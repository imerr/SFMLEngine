/* 
 * File:   Box2dDebugDraw.hpp
 * Author: iMer
 *
 * Created on 15. August 2014, 04:29
 */

#ifndef BOX2DDEBUGDRAW_HPP
#define	BOX2DDEBUGDRAW_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
namespace engine {
    class Scene;
	class Box2dDebugDraw : public sf::NonCopyable, public b2Draw, public sf::Drawable {
	protected:
		Scene* m_scene;
		sf::RenderTexture m_texture;
		sf::Vertex m_vertices[2];
		bool m_isInitialized;
	public:
		Box2dDebugDraw(Scene* scene);
		virtual ~Box2dDebugDraw();
		void Begin();
		void End();
		bool IsInitialized() const;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		/// Draw a closed polygon provided in CCW order.
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		/// Draw a solid closed polygon provided in CCW order.
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

		/// Draw a circle.
		virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

		/// Draw a solid circle.
		virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

		/// Draw a line segment.
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

		/// Draw a transform. Choose your own length scale.
		/// @param xf a transform.
		virtual void DrawTransform(const b2Transform& xf);

		void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	};
}

#endif	/* BOX2DDEBUGDRAW_HPP */

