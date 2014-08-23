/* 
 * File:   Game.cpp
 * Author: iMer
 * 
 * Created on 2. Juli 2014, 23:50
 */

#include <iostream>
#include <thread>
#include "Game.hpp"
#include <sstream>

namespace engine {

    Game::Game() : m_window(sf::VideoMode(1024, 576), "SFML works!"), m_scene(nullptr), m_running(true), m_fps(0), m_tps(0) {
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
        sf::Clock t;
        t.restart();
        m_window.setActive(true);
        while (m_running) {
            m_lastLogicUpdateMutex.lock();
            sf::Time delta = m_lastLogicUpdate.getElapsedTime();
            m_lastLogicUpdateMutex.unlock();
            m_window.clear(sf::Color::White);
            if (m_scene) {
                m_scene->draw(m_window, sf::RenderStates::Default, t.restart().asSeconds());
            }
            m_window.display();
            m_fps++;

        }
    }

    void Game::LogicLoop() {
        sf::Time interval = sf::seconds(1.0f / 60.0f); // 60cycles/s
        sf::Clock timer;
        float sec=0;
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
                sf::sleep(interval - delta);
                sec+=interval.asSeconds();
            }else{
                sec+=delta.asSeconds();
            }
            
            m_tps++;
            if (sec > 1){
                std::ostringstream ss;
                ss << m_fps << " FPS " << m_tps << " TPS";
                m_window.setTitle(ss.str());
                m_fps=0;
                m_tps=0;
                sec=0;
            }
        }
    }

    sf::RenderWindow* Game::GetWindow() {
        return &m_window;
    }
    sf::Vector2f Game::GetMousePosition(){
        return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    }
}