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

    Light::Light() : m_active(true), m_lightColor(sf::Color::White), m_radius(10), m_rayCount(256) {
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
        for (m_currentVert = 1; m_currentVert < m_rayCount + 2; m_currentVert++) {
            float t = 2 * util::fPI * static_cast<float> (m_currentVert - 1) / static_cast<float> (m_rayCount - 1);
            float x = cosf(t) * m_radius;
            float y = sinf(t) * m_radius;
            m_vertices[m_currentVert].position.x = x;
            m_vertices[m_currentVert].position.y = y;
            m_vertices[m_currentVert].color = sf::Color::Black;
            GetScene()->GetWorld()->RayCast(this, b2Vec2(pos.x / m_scene->GetPixelMeterRatio(), pos.y / m_scene->GetPixelMeterRatio()), b2Vec2((pos.x + x) / m_scene->GetPixelMeterRatio(), (pos.y + y) / m_scene->GetPixelMeterRatio()));
        }
    }

    void Light::DrawLight(sf::RenderTarget& target, sf::RenderStates states) {
        std::lock_guard<std::mutex> lg(m_mutex);
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
        m_vertices[m_currentVert].position.x *=fraction;
        m_vertices[m_currentVert].position.y *=fraction;
        m_vertices[m_currentVert].color.r = 255 * (1-fraction);
        m_vertices[m_currentVert].color.g = 255 * (1-fraction);
        m_vertices[m_currentVert].color.b = 255 * (1-fraction);

        return fraction;
    }
}

