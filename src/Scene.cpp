/* 
 * File:   Scene.cpp
 * Author: iMer
 * 
 * Created on 3. Juli 2014, 01:01
 */

#include "Scene.hpp"
#include "Game.hpp"
#include "Light.hpp"
#include <iostream>
#include <mutex>
#include "Light.hpp"
namespace engine {
    b2Vec2 Scene::default_gravity(0, 0);

    Scene::Scene(Game* game) : m_game(game), m_pixToM(20.0f), m_debugDraw(this), m_lightSystem(this) {
        m_scene = this;
        m_world = new b2World(default_gravity);
        m_world->SetDebugDraw(&m_debugDraw);
        m_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
        //m_lightSystem.SetScene(this);
    }

    LightSystem* Scene::GetLightSystem() {
        return &m_lightSystem;
    }

    Scene::~Scene() {
        delete m_world;
    }

    void Scene::SetGame(Game* game) {
        m_game = game;
        //m_lightSystem.Initialize(m_game->GetWindow()->getSize().x, m_game->GetWindow()->getSize().y);
    }

    Game* Scene::GetGame() const {
        return m_game;
    }

    b2World* Scene::GetWorld() {
        return m_world;
    }

    float Scene::MeterToPixel(float m) {
        return m_pixToM*m;
    }

    float Scene::GetPixelMeterRatio() const {
        return m_pixToM;
    }

    void Scene::PostDraw(sf::RenderTarget& target, sf::RenderStates states) {
        // m_lightSystem.draw(target, states);
        m_mutexDebug.lock();
        if (m_debugDraw.IsInitialized()) {
        //    m_debugDraw.draw(target, states);
        }
        m_mutexDebug.unlock();
        m_lightSystem.draw(target, states);
    }

    void Scene::OnUpdate(sf::Time interval) {
        m_world->Step(interval.asSeconds(), 8, 3); // TODO: tweakable iterations? currently the box2d recommended ones
        m_mutexDebug.lock();
        m_debugDraw.Begin();
        m_world->DrawDebugData();
        m_debugDraw.End();
        m_mutexDebug.unlock();
        m_lightSystem.update(interval);
    }

}

