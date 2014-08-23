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

    Scene::Scene(Game* game) : Node::Node(this), m_game(game), m_pixToM(20.0f), m_debugDraw(this), m_lightSystem(this), m_debug(false), m_ui(this) {
        m_world = new b2World(default_gravity);
        m_world->SetDebugDraw(&m_debugDraw);
        m_debugDraw.SetFlags(b2Draw::e_shapeBit);
    }

    LightSystem* Scene::GetLightSystem() {
        return &m_lightSystem;
    }

    void Scene::SetDebug(bool debug) {
        m_debug = debug;
    }

    bool Scene::IsDebug() const {
        return m_debug;
    }

    Scene::~Scene() {
        delete m_world;
    }

    void Scene::SetGame(Game* game) {
        m_game = game;
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

    void Scene::PostDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
        if (m_debug) {
            m_mutexDebug.lock();
            if (m_debugDraw.IsInitialized()) {
                m_debugDraw.draw(target, states);
            }
            m_mutexDebug.unlock();
        }
        m_lightSystem.draw(target, states);
        m_ui.draw(target, states, delta);
    }

    void Scene::OnUpdate(sf::Time interval) {
        m_world->Step(interval.asSeconds(), 8, 3); // TODO: tweakable iterations? currently the box2d recommended ones
        if (m_debug) {
            m_mutexDebug.lock();
            m_debugDraw.Begin();
            m_world->DrawDebugData();
            m_debugDraw.End();
            m_mutexDebug.unlock();
        }
        m_lightSystem.update(interval);
        m_ui.update(interval);
    }

    uint8_t Scene::GetType() const {
        return NT_SCENE;
    }

    bool Scene::initialize(Json::Value& root) {
        if (root["gravity"].isArray()) {
            m_world->SetGravity(b2Vec2(root["gravity"].get(0u, 0).asFloat(), root["gravity"].get(1u, 0).asFloat()));
        } else if (root["gravity"].isObject()) {
            m_world->SetGravity(b2Vec2(root["gravity"].get("x", 0).asFloat(), root["gravity"].get("y", 0).asFloat()));
        }
        m_debug = root.get("debug", false).asBool();
        auto light = root["light"];
        if (!light.empty() && !light.isNull()) {
            m_lightSystem.SetEnabled(light.get("enabled", true).asBool());
            if (light["ambient"].isArray()) {
                m_lightSystem.SetAmbientColor(sf::Color(light["ambient"].get(0u, 255).asInt(), light["ambient"].get(1u, 255).asInt(), light["ambient"].get(2u, 255).asInt(), light["ambient"].get(3u, 255).asInt()));
            } else if (light["ambient"].isInt()) {
                unsigned int lc = light["ambient"].asInt();
                m_lightSystem.SetAmbientColor(sf::Color(lc & 0xFF0000, lc & 0xFF00, lc & 0xFF, lc & 0xFF000000));
            }
        }
        return true;
    }
}

