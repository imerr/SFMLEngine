#ifndef ENGINE_PARALLAXBACKGROUND_HPP
#define ENGINE_PARALLAXBACKGROUND_HPP


#include <Engine/SpriteNode.hpp>

namespace engine {
	class ParallaxBackground : public engine::SpriteNode {
	public:
		ParallaxBackground(engine::Scene* scene);

		~ParallaxBackground();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states, float delta);


	protected:


	};
}


#endif //ENGINE_PARALLAXBACKGROUND_HPP
