#ifndef ENGINE_LOADINGSCENE_HPP
#define    ENGINE_LOADINGSCENE_HPP

#include "Scene.hpp"

namespace engine {
	class LoadingScene : public Scene {
	protected:
		Scene* m_old;
		std::atomic<Scene*> m_new;
		std::atomic<bool> m_done;
		bool m_deleteAfterSwitch;
	public:
		LoadingScene(Game* game);

		virtual ~LoadingScene();

		void Switch(Scene* old, Scene* newScene);

		void SetDeleteAfterSwitch(bool deleteAfter) {
			m_deleteAfterSwitch = deleteAfter;
		};

	protected:
		virtual void OnUpdate(sf::Time interval);

		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
	};

}

#endif	/* ENGINE_LOADINGSCENE_HPP */

