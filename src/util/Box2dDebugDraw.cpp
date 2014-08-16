/* 
 * File:   Box2dDebugDraw.cpp
 * Author: iMer
 * 
 * Created on 15. August 2014, 04:29
 */

#include <vector>

#include "Box2dDebugDraw.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include <iostream>
#include "misc.hpp"
namespace engine {
    namespace util {

        sf::Color FromB2Color(b2Color c) {
            return sf::Color(minmax<float>(0, c.r * 255, 255), minmax<float>(0, c.g * 255, 255), minmax<float>(0, c.b * 255, 255), minmax<float>(0, c.a * 128, 255));
        }

        Box2dDebugDraw::Box2dDebugDraw(Scene* scene) : m_scene(scene), m_isInitialized(false) {
            auto size = m_scene->GetGame()->GetWindow()->getSize();
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
            s.setTexture(m_texture.getTexture());
            target.draw(s, states);
        }

        void Box2dDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
            sf::ConvexShape s;
            s.setPointCount(vertexCount);
            for (int32 i = 0; i < vertexCount; i++) {
                s.setPoint(i, sf::Vector2f(m_scene->PixelToMeters(vertices[i].x), m_scene->PixelToMeters(vertices[i].y)));
            }
            s.setOutlineThickness(5);
            s.setOutlineColor(FromB2Color(color));
            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
            sf::ConvexShape s;
            s.setPointCount(vertexCount);
            for (int32 i = 0; i < vertexCount; i++) {
                s.setPoint(i, sf::Vector2f(m_scene->PixelToMeters(vertices[i].x), m_scene->PixelToMeters(vertices[i].y)));
            }
            s.setFillColor(FromB2Color(color));
            m_texture.draw(s);
        }

        void Box2dDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
            sf::CircleShape s;
            s.setRadius(m_scene->PixelToMeters(radius));
            s.setFillColor(sf::Color(0, 0, 0, 0));
            s.setOutlineThickness(5);
            s.setOutlineColor(FromB2Color(color));
            s.setPosition(m_scene->PixelToMeters(center.x), m_scene->PixelToMeters(center.y));
        }

        void Box2dDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
            sf::CircleShape s;
            s.setRadius(m_scene->PixelToMeters(radius));
            s.setFillColor(FromB2Color(color));
            s.setPosition(m_scene->PixelToMeters(center.x), m_scene->PixelToMeters(center.y));
        }

        void Box2dDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
            incVertVec(2);
            for (int i = 0; i < 2; i++) {
                m_vertices[i].color.a = color.a;
                m_vertices[i].color.r = color.r;
                m_vertices[i].color.g = color.g;
                m_vertices[i].color.b = color.b;
            }
            m_vertices[0].position.x = m_scene->PixelToMeters(p1.x);
            m_vertices[0].position.y = m_scene->PixelToMeters(p1.y);
            m_vertices[1].position.x = m_scene->PixelToMeters(p2.x);
            m_vertices[1].position.y = m_scene->PixelToMeters(p2.y);
            m_texture.draw(m_vertices.data(), 2, sf::Lines);
        }

        void Box2dDebugDraw::DrawTransform(const b2Transform& xf) {
        }

        void Box2dDebugDraw::incVertVec(size_t c) {
            if (m_vertices.size() < c) {
                m_vertices.resize(c);
            }
        }
    }
}
