#include "Scene.hpp"
#include "Game.hpp"
#include "util/misc.hpp"
#include "util/Box2dDebugDraw.hpp"


#include <iostream>
#include <vector>
namespace engine {
    namespace util {

        sf::Color FromB2Color(b2Color c) {
            return sf::Color(
					minmax<uint8_t>(0, static_cast<uint8_t>(c.r * 255), 255),
					minmax<uint8_t>(0, static_cast<uint8_t>(c.g * 255), 255),
					minmax<uint8_t>(0, static_cast<uint8_t>(c.b * 255), 255));
        }

        Box2dDebugDraw::Box2dDebugDraw(Scene* scene) : m_scene(scene), m_isInitialized(false) {
            auto size = m_scene->GetGame()->GetWindow()->getView().getSize();
            m_texture.create(size.x, size.y);
        }

        Box2dDebugDraw::~Box2dDebugDraw() {
        }

        void Box2dDebugDraw::Begin() {
            m_texture.setActive(true);
            m_texture.clear(sf::Color(0, 0, 0, 0));
        }

        void Box2dDebugDraw::End() {
            m_texture.display();
            m_texture.setActive(false);
            m_isInitialized = true;
        }

        bool Box2dDebugDraw::IsInitialized() const {
            return m_isInitialized;
        }

        void Box2dDebugDraw::draw(sf::RenderTarget& target, sf::RenderStates states) const {
            sf::Sprite s;
            sf::Transformable tr;
            auto window = m_scene->GetGame()->GetWindow();
            tr.setPosition(window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            states.transform *= tr.getTransform();
            states.blendMode = sf::BlendAdd;
            s.setTexture(m_texture.getTexture());
            target.draw(s, states);
        }

        void Box2dDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
            sf::ConvexShape s;
            s.setPointCount(vertexCount);
			auto window = m_scene->GetGame()->GetWindow();
			sf::Vector2f p (window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            for (int32 i = 0; i < vertexCount; i++) {
                s.setPoint(i, sf::Vector2f(m_scene->MeterToPixel(vertices[i].x) - p.x, m_scene->MeterToPixel(vertices[i].y) - p.y));
            }
            s.setOutlineThickness(5);
            s.setOutlineColor(FromB2Color(color));
            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
            sf::ConvexShape s;
            s.setPointCount(vertexCount);
			auto window = m_scene->GetGame()->GetWindow();
			sf::Vector2f p (window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            for (int32 i = 0; i < vertexCount; i++) {
                s.setPoint(i, sf::Vector2f(m_scene->MeterToPixel(vertices[i].x) - p.x, m_scene->MeterToPixel(vertices[i].y) - p.y));
            }
            s.setFillColor(FromB2Color(color));
            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
            sf::CircleShape s;
            s.setRadius(m_scene->MeterToPixel(radius));
            s.setFillColor(sf::Color(0, 0, 0, 0));
            s.setOutlineThickness(5);
            s.setOutlineColor(FromB2Color(color));

			auto window = m_scene->GetGame()->GetWindow();
			sf::Vector2f p (window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            s.setPosition(m_scene->MeterToPixel(center.x)-m_scene->MeterToPixel(radius) - p.x, m_scene->MeterToPixel(center.y)+m_scene->MeterToPixel(radius) - p.y);
            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
            sf::CircleShape s;
            s.setRadius(m_scene->MeterToPixel(radius));
            s.setOrigin(m_scene->MeterToPixel(radius),m_scene->MeterToPixel(radius));
            s.setFillColor(FromB2Color(color));
			auto window = m_scene->GetGame()->GetWindow();
			sf::Vector2f p (window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            s.setPosition(m_scene->MeterToPixel(center.x) - p.x, m_scene->MeterToPixel(center.y) - p.y);

            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
            for (int i = 0; i < 2; i++) {
                m_vertices[i].color = FromB2Color(color);
            }

			auto window = m_scene->GetGame()->GetWindow();
			sf::Vector2f p (window->getView().getCenter().x - (window->getView().getSize().x / 2), window->getView().getCenter().y - (window->getView().getSize().y / 2));
            m_vertices[0].position.x = m_scene->MeterToPixel(p1.x) - p.x;
            m_vertices[0].position.y = m_scene->MeterToPixel(p1.y) - p.y;
            m_vertices[1].position.x = m_scene->MeterToPixel(p2.x) - p.x;
            m_vertices[1].position.y = m_scene->MeterToPixel(p2.y) - p.y;
            m_texture.draw(m_vertices, 2, sf::Lines);
        }

        void Box2dDebugDraw::DrawTransform(const b2Transform& xf) {
        }

    }
}
