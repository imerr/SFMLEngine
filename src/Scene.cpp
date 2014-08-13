/* 
 * File:   Scene.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:01
 */

#include "Scene.hpp"
#include "Game.hpp"
namespace engine {

    Scene::Scene() {
        m_lightSystem.SetScene(this);
    }

    Scene::Scene(const Scene& orig) {
    }

    Scene::~Scene() {
    }

    void Scene::SetGame(Game* game) {
        m_game = game;
        //m_lightSystem.Initialize(m_game->GetWindow()->getSize().x, m_game->GetWindow()->getSize().y);
    }

    Game* Scene::GetGame() const {
        return m_game;
    }

    /*LightSystem* Scene::GetLightSystem() {
        return &m_lightSystem;
    }*/

    void Scene::PostDraw(sf::RenderTarget& target, sf::RenderStates states) const {
       // m_lightSystem.draw(target, states);
    }

    void Scene::OnUpdate(sf::Time delta) {
        //m_lightSystem.update(delta);
    }
}

