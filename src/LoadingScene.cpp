#include "LoadingScene.hpp"
#include "Engine/Game.hpp"
namespace engine {
	LoadingScene::LoadingScene(Game* game): Scene(game), m_done(false), m_new(nullptr), m_old(nullptr) {
	}

	LoadingScene::~LoadingScene() {
	}
	
	void LoadingScene::OnUpdate(sf::Time interval) {
		if (m_done) {
			delete m_old;
			m_game->SetScene(m_new);
		}
	}
	
	void LoadingScene::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		m_done = true;
		Scene::OnDraw(target, states, delta);
	}
	void LoadingScene::Switch(Scene* old, Scene* new_) {
		m_old = old;
		m_new = new_;
		m_done = false;
	}
}

