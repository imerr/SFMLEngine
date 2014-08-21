/* 
 * File:   Scene.hpp
 * Author: iMer
 *
 * Created on 3. Juli 2014, 01:01
 */

#ifndef ENGINE_SCENE_HPP
#define	ENGINE_SCENE_HPP
#include "Node.hpp"
#include "Box2D/Box2D.h"
#include "util/Box2dDebugDraw.hpp"
#include "LightSystem.hpp"
namespace engine {
    class Game;
    class Light;
    class Scene : public Node {
    public:
        static b2Vec2 default_gravity;
    protected:
        Game* m_game;
        b2World* m_world;
        float m_pixToM;
        util::Box2dDebugDraw m_debugDraw;
        std::mutex m_mutexDebug;
        LightSystem m_lightSystem;
        bool m_debug;
    public:
        Scene(Game* game);
        virtual ~Scene();
        void SetGame(Game* game);
        Game* GetGame() const;
        b2World* GetWorld();
        float MeterToPixel(float m);
        float GetPixelMeterRatio() const;
        void AddLight(Light* light);
        void RemoveLight(Light* light);
        LightSystem* GetLightSystem();
        void SetDebug(bool debug);
        bool IsDebug() const;
        virtual uint8_t GetType() const;
    private:
        virtual void OnUpdate(sf::Time interval);
        virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states);
    };
}

#endif	/* ENGINE_SCENE_HPP */

