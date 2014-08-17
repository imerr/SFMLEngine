/* 
 * File:   Light.hpp
 * Author: iMer
 *
 * Created on 17. August 2014, 07:31
 */

#ifndef LIGHT_HPP
#define	LIGHT_HPP

#include "Node.hpp"

namespace engine {

    class Light : public Node, public b2RayCastCallback {
    protected:
        bool m_active;
        sf::Color m_lightColor;
        float m_radius;
        std::vector<sf::Vertex> m_vertices;
        size_t m_rayCount;
        size_t m_currentVert;
    public:
        Light();
        virtual ~Light();
        void SetActive(bool active);
        bool IsActive() const;
        void SetRadius(float radius);
        float GetRadius() const;
        void SetLightColor(sf::Color lightColor);
        sf::Color GetLightColor() const;
        virtual void OnUpdate(sf::Time interval);
        virtual void DrawLight(sf::RenderTarget& target, sf::RenderStates states);
        void SetRayCount(size_t rayCount);
        size_t GetRayCount() const;
    protected: // Prevent it being called directly
        virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

    };
}

#endif	/* LIGHT_HPP */

