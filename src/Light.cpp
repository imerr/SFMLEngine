/*
 * File:   Light.cpp
 * Author: iMer
 *
 * Created on 17. August 2014, 07:31
 */

#include "Light.hpp"
#include "Scene.hpp"
#include "util/math.hpp"
#include "util/misc.hpp"
#include <iostream>
#include "Game.hpp"

namespace engine {

    Light::Light(Scene *scene) : Node(scene), m_active(true), m_lightColor(sf::Color::White), m_radius(200),
                                 m_rayCount(256), m_blocked(false), m_angle(0),
                                 m_openingAngle(util::fPI * 2) {
        m_vertices.resize(m_rayCount + 2);
        scene->GetLightSystem()->AddLight(this);
        m_opaque = true;
    }

    void Light::SetRadius(float radius, bool setRayCount) {
        m_radius = radius;
        if (setRayCount) {
            SetRayCount(static_cast<size_t>((m_radius * m_openingAngle) / 40));
        }
    }

    float Light::GetRadius() const {
        return m_radius;
    }

    void Light::SetLightColor(sf::Color lightColor) {
        m_lightColor = lightColor;
        m_vertices[0].color = m_lightColor;
    }

    sf::Color Light::GetLightColor() const {
        return m_lightColor;
    }

    Light::~Light() {
        if (m_scene) {
            m_scene->GetLightSystem()->RemoveLight(this);
        }
    }

    namespace {
        void AssignLightColor(sf::Vertex &v, float f, const sf::Color &color) {
            v.color.r = static_cast<uint8_t>(color.r * (1 - f));
            v.color.g = static_cast<uint8_t>(color.g * (1 - f));
            v.color.b = static_cast<uint8_t>(color.b * (1 - f));
        }
    }

    void Light::OnUpdate(sf::Time interval) {
        std::lock_guard<std::recursive_mutex> lg(m_mutex);
        if (!m_render || !GetParent()->IsRender()) return;
        sf::Vector2f pos = GetGlobalPosition();
        const auto &v = m_scene->GetGame()->GetWindow()->getView();
        auto vr = sf::FloatRect(v.getCenter().x - v.getSize().x / 2, v.getCenter().y - v.getSize().y / 2, v.getSize().x,
                                v.getSize().y);
        if (!vr.intersects(sf::Rect<float>(pos.x - m_radius, pos.y - m_radius, 2 * m_radius, 2 * m_radius))) {
            m_blocked = true;
            return;
        }
        b2AABB center;
        center.lowerBound.x = pos.x / m_scene->GetPixelMeterRatio();
        center.lowerBound.y = pos.y / m_scene->GetPixelMeterRatio();
        float onep = (1.f / m_scene->GetPixelMeterRatio());
        center.upperBound.x = center.lowerBound.x + onep;
        center.upperBound.y = center.lowerBound.y + onep;
        CenterQuery cq(center.lowerBound.x, center.lowerBound.y);
        GetScene()->GetWorld()->QueryAABB(&cq, center);
        if (cq.hit) {
            m_blocked = true;
        } else {
            m_blocked = false;
            auto pos = GetPosition();
            float rayDistance =
                    (2 - cosf(m_openingAngle / (m_rayCount - 1))) * m_radius / m_scene->GetPixelMeterRatio();
            b2Vec2 basePos(GetPosition().x / m_scene->GetPixelMeterRatio(),
                           GetPosition().y / m_scene->GetPixelMeterRatio());
            struct edgeData {
                b2Vec2 pos;
                b2Fixture *fixture;
                int vertex;
            };
            static std::map<int, edgeData> edges;
            edges.clear();
            auto EdgeFromPos = [&, this](const b2Vec2 &p) -> edgeData * {
                float angle = atan2f(basePos.y - p.y, basePos.x - p.x) + engine::util::fPI;
                if (angle > m_angle + m_openingAngle || angle < m_angle) {
                    return nullptr;
                }
                int i = static_cast<int>(angle / util::fPI * 180);
                auto it = edges.find(i);
                if (it == edges.end()) {
                    edgeData def{basePos + m_radius / m_scene->GetPixelMeterRatio(), nullptr, 0};
                    edges.insert(std::make_pair(i, def));
                    return &edges.find(i)->second;
                }
                return &it->second;
            };
            auto aabbCallback = engine::MakeAABBQueryCallback([&, this](b2Fixture *fixture) -> bool {
                if (static_cast<Node *>(fixture->GetBody()->GetUserData())->IsOpaque())
                    return true;

                if (fixture->GetShape()->GetType() == b2Shape::e_polygon) {
                    b2PolygonShape *shape = static_cast<b2PolygonShape *>(fixture->GetShape());
                    for (size_t i = 0; i < shape->GetVertexCount(); i++) {
                        const b2Vec2 &vertex = shape->GetVertex(i);
                        b2Vec2 vertexPos = vertex + fixture->GetBody()->GetPosition();
                        auto vLen = (vertexPos - basePos).Length();
                        if (vLen < m_radius / m_scene->GetPixelMeterRatio()) {
                            auto edge = EdgeFromPos(vertexPos);
                            if (!edge) continue;
                            // Is the vertex we found better
                            b2Vec2 dif = edge->pos - basePos;
                            if (vLen < dif.Length()) {
                                edge->pos = vertexPos;
                            }
                            edge->fixture = fixture;
                            edge->vertex = i;
                        }
                    }
                }
                return true;
            });
            b2AABB aabb;
            aabb.lowerBound = b2Vec2((pos.x - m_radius) / m_scene->GetPixelMeterRatio(),
                                     (pos.y - m_radius) / m_scene->GetPixelMeterRatio());
            aabb.upperBound = b2Vec2((pos.x + m_radius) / m_scene->GetPixelMeterRatio(),
                                     (pos.y + m_radius) / m_scene->GetPixelMeterRatio());
            m_scene->GetWorld()->QueryAABB(&aabbCallback, aabb);
            float step = m_openingAngle / static_cast<float> (m_rayCount - 1);
            float angle = m_angle;
            auto it = edges.begin();
            m_vertices.resize(1); // keep the center vertex
            float f = 1.0;
            auto rayCastCallback = MakeRayCastCallback([&](b2Fixture *fixture, const b2Vec2 &point,
                                                           const b2Vec2 &normal, float32 fraction) {
                Node* n = static_cast<Node*> (fixture->GetBody()->GetUserData());
                if (n && !n->IsOpaque() && fraction < f) {
                    f = fraction;
                }
                return f;
            });
            float lastEdgeAngle = 10;
            for (size_t i = 1; i < m_rayCount + 1; i++, angle += step) {
                sf::Vertex v;
                bool had = false;
                while (it != edges.end()) {
                    float edgeAngle = (it->first * util::fPI / 180);
                    if (angle < edgeAngle || edgeAngle >= angle + step) {
                        break;
                    }
                    if (it->second.fixture == nullptr) {
                        lastEdgeAngle = it->first;
                        ++it;
                        continue;
                    }
                    f = 1.0;
                    m_scene->GetWorld()->RayCast(&rayCastCallback, basePos, it->second.pos);
                    // Check if this edge is blocked, skip if it is
                    if (!floatEqual(f, 1.0, 10.0f / m_radius)) {
                        lastEdgeAngle = it->first;
                        ++it;
                        continue;
                    }
                    had = true;
                    float edgeLengthPct =
                            m_scene->MeterToPixel((basePos - it->second.pos).Length()) / m_radius + (10.0f / m_radius);
                    auto addPoint = [&, this](b2Vec2 point) {
                        v.position.x = m_scene->MeterToPixel(point.x) - pos.x;
                        v.position.y = m_scene->MeterToPixel(point.y) - pos.y;
                        f = sqrtf(v.position.x * v.position.x + v.position.y * v.position.y) / m_radius;
                        AssignLightColor(v, f, m_lightColor);
                        m_vertices.push_back(v);
                    };
                    edgeAngle = b2Angle(basePos, it->second.pos);
                    // Check surrounding edges by using half a degree differences
                    f = 1.0;
                    b2Vec2 edge = basePos +
                                  (b2Vec2(cosf(edgeAngle - (util::fPI / 360.f)),
                                          sinf(edgeAngle - (util::fPI / 360.f))) *
                                   (m_radius / m_scene->GetPixelMeterRatio()));
                    m_scene->GetWorld()->RayCast(&rayCastCallback, basePos, edge);
                    if (f > edgeLengthPct) {
                        addPoint(basePos + (basePos - edge) * -f);
                    }
                    addPoint(it->second.pos);
                    f = 1.0;
                    edge = basePos +
                           (b2Vec2(cosf(edgeAngle + (util::fPI / 360.f)),
                                   sinf(edgeAngle + (util::fPI / 360.f))) * (m_radius / m_scene->GetPixelMeterRatio()));
                    m_scene->GetWorld()->RayCast(&rayCastCallback, basePos, edge);
                    if (f > edgeLengthPct) {
                        addPoint(basePos + (basePos - edge) * -f);
                    }
                    lastEdgeAngle = it->first;
                    ++it;
                }
                if (!floatEqual(lastEdgeAngle / 180.0f * util::fPI, angle, util::fPI/180.0f)) {
                    v.position.x = cosf(angle) * m_radius;
                    v.position.y = sinf(angle) * m_radius;
                    f = 1.0;
                    m_scene->GetWorld()->RayCast(&rayCastCallback, basePos, basePos + b2Vec2(v.position.x /
                                                                                             m_scene->GetPixelMeterRatio(),
                                                                                             v.position.y /
                                                                                             m_scene->GetPixelMeterRatio()));
                    v.position *= f;
                    AssignLightColor(v, f, m_lightColor);
                    m_vertices.push_back(v);
                }
            }
        }
    }

    void Light::DrawLight(sf::RenderTarget &target, sf::RenderStates states) {
        std::lock_guard<std::recursive_mutex> lg(m_mutex);
        if (m_blocked) {
            return;
        }
        if (!m_render || !GetParent()->IsRender()) return;
        sf::Transformable tr;
        auto window = m_scene->GetGame()->GetWindow();
        tr.setPosition(-window->getView().getCenter().x + (window->getView().getSize().x / 2) + GetGlobalPosition().x,
                       -window->getView().getCenter().y + (window->getView().getSize().y / 2) + GetGlobalPosition().y);
        states.transform *= tr.getTransform();
        target.draw(m_vertices.data(), m_vertices.size(), sf::PrimitiveType::TrianglesFan, states);

        // Debug draw
        // sf::Vertex v[2];
        // v[0] = m_vertices[0];
        // v[0].color = sf::Color::Red;
        // v[1].color = sf::Color::Red;
        // for (size_t i = 1; i < m_vertices.size(); i++) {
        //     v[1].position = m_vertices[i].position;
        //     target.draw(v, 2, sf::PrimitiveType::Lines, states);
        // }
    }

    void Light::SetRayCount(size_t rayCount) {
        m_rayCount = rayCount;
    }

    size_t Light::GetRayCount() const {
        return m_rayCount;
    }

    void Light::SetAngle(float angle) {
        m_angle = angle;
    }

    float Light::GetAngle() const {
        return m_angle;
    }

    void Light::SetOpeningAngle(float openingAngle) {
        m_openingAngle = openingAngle;
    }

    float Light::GetOpeningAngle() const {
        return m_openingAngle;
    }

    Light::CenterQuery::CenterQuery(float x, float y) : hit(false), pos(x, y) {
    }

    bool Light::CenterQuery::ReportFixture(b2Fixture *fixture) {
        Node *n = static_cast<Node *> (fixture->GetBody()->GetUserData());
        if ((!n || !n->IsOpaque()) && fixture->TestPoint(pos)) {
            hit = true;
            return false;
        }
        return true;
    }

    bool Light::initialize(Json::Value &root) {
        if (!Node::initialize(root)) {
            return false;
        }
        if (root["color"].isArray()) {
            m_lightColor.r = root["color"].get(0u, 255).asInt();
            m_lightColor.g = root["color"].get(1u, 255).asInt();
            m_lightColor.b = root["color"].get(2u, 255).asInt();
            m_lightColor.a = root["color"].get(3u, 255).asInt();
            SetLightColor(m_lightColor);
        } else if (root["color"].isInt()) {
            unsigned int lc = root["color"].asInt();
            m_lightColor = sf::Color(lc & 0xFF0000 >> 16, lc & 0xFF00 >> 8, lc & 0xFF, lc & 0xFF000000 >> 24);
        }
        m_radius = root.get("radius", 200).asFloat();
        m_angle = root.get("angle", 0).asFloat() * util::fPI / 180;
        // min prevents overdrawing
        m_openingAngle = util::min(root.get("openingAngle", 360).asFloat() * util::fPI / 180, util::fPI * 2);
        return true;
    }
}

