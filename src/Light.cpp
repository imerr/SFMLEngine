/* 
 * File:   Light.cpp
 * Author: iMer
 * 
 * Created on 17. August 2014, 07:31
 */

#include "Light.hpp"
#include "Scene.hpp"
#include "util/math.hpp"
#include <iostream>
namespace engine {

    Light::Light(Scene* scene) : Node::Node(scene), m_active(true), m_lightColor(sf::Color::White), m_radius(10), m_rayCount(256), m_blocked(false), m_raycastFraction(1.0f) {
        m_vertices.resize(m_rayCount + 2);
    }

    void Light::SetActive(bool active) {
        m_active = active;
    }

    bool Light::IsActive() const {
        return m_active;
    }

    void Light::SetRadius(float radius) {
        m_radius = radius;
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

    void Light::OnUpdate(sf::Time interval) {
        std::lock_guard<std::mutex> lg(m_mutex);
        sf::Vector2f pos = GetGlobalPosition();
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
            for (size_t i = 1; i < m_rayCount + 2; i++) {
                float t = 2 * util::fPI * static_cast<float> (i - 1) / static_cast<float> (m_rayCount - 1);
                float x = cosf(t) * m_radius;
                float y = sinf(t) * m_radius;
                m_vertices[i].position.x = x;
                m_vertices[i].position.y = y;
                m_vertices[i].color = sf::Color::Black;
                m_raycastFraction = 1.0f;
                GetScene()->GetWorld()->RayCast(this, b2Vec2(pos.x / m_scene->GetPixelMeterRatio(), pos.y / m_scene->GetPixelMeterRatio()), b2Vec2((pos.x + x) / m_scene->GetPixelMeterRatio(), (pos.y + y) / m_scene->GetPixelMeterRatio()));
                if (m_raycastFraction < 1.0f) {
                    m_vertices[i].position.x *= m_raycastFraction;
                    m_vertices[i].position.y *= m_raycastFraction;
                    m_vertices[i].color.r = 255 * (1 - m_raycastFraction);
                    m_vertices[i].color.g = 255 * (1 - m_raycastFraction);
                    m_vertices[i].color.b = 255 * (1 - m_raycastFraction);
                }
            }
        }
    }

    void Light::DrawLight(sf::RenderTarget& target, sf::RenderStates states) {
        std::lock_guard<std::mutex> lg(m_mutex);
        if (m_blocked) {
            return;
        }
        states.transform *= getTransform();
        target.draw(m_vertices.data(), m_rayCount + 1, sf::PrimitiveType::TrianglesFan, states);
    }

    void Light::SetRayCount(size_t rayCount) {
        m_rayCount = rayCount;
        m_vertices.resize(m_rayCount + 2);
        SetLightColor(m_lightColor); // lazy
    }

    size_t Light::GetRayCount() const {
        return m_rayCount;
    }

    float32 Light::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
        Node* n = static_cast<Node*>(fixture->GetBody()->GetUserData());
        if ((!n || !n->IsOpaque()) && fraction < m_raycastFraction) {
            m_raycastFraction = fraction;
        }
        return m_raycastFraction;
    }

    Light::CenterQuery::CenterQuery(float x, float y) : hit(false), pos(x, y) {
    }

    bool Light::CenterQuery::ReportFixture(b2Fixture* fixture) {
        Node* n = static_cast<Node*>(fixture->GetBody()->GetUserData());
        if ((!n || !n->IsOpaque()) && fixture->TestPoint(pos)) {
            hit = true;
            return false;
        }
        return true;
    }
}

