/* 
 * File:   Light.hpp
 * Author: iMer
 *
 * Created on 17. August 2014, 07:31
 */

#ifndef LIGHT_HPP
#define    LIGHT_HPP

#include "Node.hpp"

namespace engine {

	class Light : public Node {

		class CenterQuery : public b2QueryCallback {
		public:
			bool hit;
			Node* node;
			b2Vec2 pos;

			CenterQuery(float x, float y);

			virtual bool ReportFixture(b2Fixture* fixture);
		};

	protected:
		sf::Color m_lightColor;
		float m_radius;
		std::vector<sf::Vertex> m_vertices;
		size_t m_rayCount;
		bool m_blocked;
		float m_angle;
		float m_openingAngle;
	public:
		Light(Scene* scene);

		virtual ~Light();

		void SetRadius(float radius, bool setRayCount = true);

		float GetRadius() const;

		void SetLightColor(sf::Color lightColor);

		sf::Color GetLightColor() const;

		virtual void DrawLight(sf::RenderTarget& target, sf::RenderStates states);

		void SetRayCount(size_t rayCount);

		size_t GetRayCount() const;

		void SetAngle(float angle);

		float GetAngle() const;

		void SetOpeningAngle(float openingAngle);

		float GetOpeningAngle() const;

		virtual bool initialize(Json::Value& root);

	protected:
		virtual void OnUpdate(sf::Time interval);

	};
}

#endif	/* LIGHT_HPP */

