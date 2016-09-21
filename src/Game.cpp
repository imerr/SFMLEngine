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

    Game::Game(uint32_t width, uint32_t height, bool multithreaded) : m_window(sf::VideoMode(width, height), "Loading.."),
			m_scene(nullptr), m_running(true), m_fps(0), m_tps(0), 
			m_focus(true), m_clearColor(sf::Color::White), m_loadingScene(this), m_multithreaded(multithreaded) {
		m_window.setVerticalSyncEnabled(true);
		sf::View view = m_window.getDefaultView();
		view.setSize(width, height);
		view.setCenter(width/2, height/2);
		m_window.setView(view);
    }

    Game::~Game() {
    }

    void Game::run() {
		std::thread* gt = nullptr;
		if (m_multithreaded) {
			m_window.setActive(false);
			gt = new std::thread(std::bind(std::mem_fn(&Game::GraphicLoop), this));
		}
        LogicLoop();
		if (gt) {
			gt->join(); // Prevent crash if thread is still running
			delete gt;
		}
    }

    void Game::GraphicLoop() {
		if (m_multithreaded) {
			sf::Clock t;
			t.restart();
			m_window.setActive(true);
			while (m_running) {
				m_window.clear(m_clearColor);
				if (m_scene) {
					m_scene->draw(m_window, sf::RenderStates::Default, t.restart().asSeconds());
				}
				m_window.display();
				m_fps++;
			}
		}
    }

    void Game::LogicLoop() {
        sf::Time interval = sf::seconds(1.0f / 60.0f); // 60cycles/s
        sf::Clock timer;
        float sec = 0;
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
                } else if (event.type == sf::Event::LostFocus) {
                    m_focus = false;
                } else if (event.type == sf::Event::GainedFocus) {
                    m_focus = true;
                } else if (event.type == sf::Event::KeyPressed) {
                    if (m_focus) {
                        OnKeyDown.Fire(event.key);
                    }
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (m_focus) {
                        OnMouseClick.Fire(event.mouseButton);
                    }
                }
            }
            m_scene->update(interval);
            OnUpdate();
			if (!m_multithreaded) {
				m_window.clear(sf::Color::White);
				if (m_scene) {
					m_scene->draw(m_window, sf::RenderStates::Default, interval.asSeconds());
				}
				m_window.display();
				m_fps++;
			}
            sf::Time delta = timer.restart();
            if (delta < interval) {
                sf::sleep(interval - delta);
                sec += interval.asSeconds();
            } else {
                sec += delta.asSeconds();
            }

            m_tps++;
            if (sec > 1) {
                std::ostringstream ss;
                ss << m_windowTitle << "   " << m_fps << " FPS " << m_tps << " TPS";
                m_window.setTitle(ss.str());
                m_fps = 0;
                m_tps = 0;
                sec = 0;
            }
        }
    }

    sf::RenderWindow* Game::GetWindow() {
        return &m_window;
    }

    sf::Vector2f Game::GetMousePosition() {
        return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    }

    bool Game::IsFocus() const {
        return m_focus;
    }

    Scene* Game::GetScene() const {
        return m_scene;
    }
}