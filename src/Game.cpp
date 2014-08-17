/* 
 * File:   Game.cpp
 * Author: iMer
 * 
 * Created on 2. Juli 2014, 23:50
 */

#include <iostream>
#include <thread>
#include "Game.hpp"


namespace engine {

    Game::Game() : m_window(sf::VideoMode(1024, 576), "SFML works!"), m_scene(nullptr), m_running(true) {
    }

    Game::Game(const Game& orig) {
    }

    Game::~Game() {
    }

    void Game::run() {
        m_window.setActive(false);
        std::thread graphics(std::bind(std::mem_fn(&Game::GraphicLoop), this));
        LogicLoop();
        graphics.join(); // Prevent crash if thread is still running
    }

    void Game::GraphicLoop() {
        m_window.setActive(true);
        while (m_running) {
            m_lastLogicUpdateMutex.lock();
            sf::Time delta = m_lastLogicUpdate.getElapsedTime();
            m_lastLogicUpdateMutex.unlock();
            sf::Color clearColor(15, 235, 165);
            m_window.clear(clearColor);
            if (m_scene) {
                m_scene->draw(m_window, sf::RenderStates::Default, delta.asSeconds());
            }
            m_window.display();
        }
    }

    void Game::LogicLoop() {
        sf::Time interval = sf::seconds(1.0f / 60.0f); // 60cycles/s
        sf::Clock timer;
        timer.restart();
        while (m_running) {
            m_lastLogicUpdateMutex.lock();
            m_lastLogicUpdate.restart();
            m_lastLogicUpdateMutex.unlock();
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    // TODO: implement events/callbacks
                    m_window.close();
                    m_running = false;
                }
            }
            m_scene->update(interval);
            sf::Time delta = timer.restart();
            if (delta < interval) {
                std::cout << "Sleeping " << (interval - delta).asSeconds() << "/" << interval.asSeconds() << " = " << (interval - delta).asSeconds() / interval.asSeconds() << "%" << std::endl;
                sf::sleep(interval - delta);
            }

        }
    }

    const sf::RenderWindow* Game::GetWindow() const {
        return &m_window;
    }
}