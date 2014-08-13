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
namespace engine {

    class Game {
    public:
        Game();
        Game(const Game& orig);
        virtual ~Game();
        void run();
        const sf::RenderWindow* GetWindow() const;
    protected:
        sf::RenderWindow m_window;
        Scene* m_scene;
        //std::map<uint8_t, Scene> m_scenes;
    };

}

#endif	/* ENGINE_GAME_HPP */

