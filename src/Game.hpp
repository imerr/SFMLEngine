/* 
 * File:   Game.hpp
 * Author: iMer
 *
 * Created on 2. Juli 2014, 23:50
 */

#ifndef ENGINE_GAME_HPP
#define	ENGINE_GAME_HPP
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include <atomic>
namespace engine {

    class Game {
    public:
        
    protected:
        sf::RenderWindow m_window;
        Scene* m_scene;
        std::atomic<bool> m_running;
        sf::Clock m_lastLogicUpdate;
        sf::Mutex m_lastLogicUpdateMutex;
        // stats
        std::atomic<int> m_fps;
        int m_tps;
    public:
        Game();
        Game(const Game& orig);
        virtual ~Game();
        void run();
        void GraphicLoop();
        void LogicLoop();
        sf::RenderWindow* GetWindow();
        // Helper
        sf::Vector2f GetMousePosition();
    };

}

#endif	/* ENGINE_GAME_HPP */

