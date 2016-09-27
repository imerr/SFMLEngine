#include "LoadingScene.hpp"
#include "Engine/Game.hpp"

namespace engine {
	LoadingScene::LoadingScene(Game* game) : Scene(game), m_done(false), m_new(nullptr), m_old(nullptr),
											 m_deleteAfterSwitch(true) {
	}

	LoadingScene::~LoadingScene() {
	}

	void LoadingScene::OnUpdate(sf::Time interval) {
		if (m_new.load() && m_done) {
			if (m_deleteAfterSwitch) {
				delete m_old;
			}
			m_game->SetScene(m_new.load());
		}
	}

	void LoadingScene::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		if (m_new.load()) {
			m_done = true;
		}
		Scene::OnDraw(target, states, delta);
	}

	void LoadingScene::Switch(Scene* old, Scene* newScene) {
		m_old = old;
		m_new = newScene;
		m_done = false;
		m_game->SetScene(this);
	}
}

