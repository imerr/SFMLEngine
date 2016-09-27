#ifndef ENGINE_LOADINGSCENE_HPP
#define    ENGINE_LOADINGSCENE_HPP

#include "Scene.hpp"

namespace engine {
	class LoadingScene : public Scene {
	protected:
		Scene* m_old;
		Scene* m_new;
		std::atomic<bool> m_done;
	public:
		LoadingScene(Game* game);

		virtual ~LoadingScene();

		void Switch(Scene* old, Scene* new_);

	protected:
		virtual void OnUpdate(sf::Time interval);

		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
	};

}

#endif	/* ENGINE_LOADINGSCENE_HPP */

