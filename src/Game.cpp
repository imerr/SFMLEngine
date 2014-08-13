/* 
 * File:   Game.cpp
 * Author: iMer
 * 
 * Created on 2. Juli 2014, 23:50
 */

#include <iostream>

#include "Game.hpp"


namespace engine {

    Game::Game() : m_window(sf::VideoMode(1024, 576), "SFML works!"), m_scene(nullptr) {

    }

    Game::Game(const Game& orig) {
    }

    Game::~Game() {
    }

    void Game::run() {
        sf::Clock timer;
        timer.restart();
        while (m_window.isOpen()) {
            sf::Time delta =  timer.restart();
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }
            m_scene->update(delta);
            sf::Color clearColor(51, 63, 76);
            m_window.clear(clearColor);
            if (m_scene) {
                m_window.draw(*m_scene);
            }
            m_window.display();
        }
    }

    const sf::RenderWindow* Game::GetWindow() const {
        return &m_window;
    }
}