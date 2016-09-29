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

	Game::Game(uint32_t width, uint32_t height, bool multithreaded) : m_window(sf::VideoMode(width, height),
																			   "Loading.."),
																	  m_scene(nullptr), m_running(true), m_fps(0),
																	  m_tps(0),
																	  m_focus(true), m_clearColor(sf::Color::White),
																	  m_loadingScene(this),
																	  m_multithreaded(multithreaded) {
		m_window.setVerticalSyncEnabled(true);
		sf::View view = m_window.getDefaultView();
		view.setSize(static_cast<float>(width), static_cast<float>(height));
		view.setCenter(width / 2.f, height / 2.f);
		m_window.setView(view);
	}

	Game::~Game() {
		// loading scene children need to be deleted since they might rely
		// on game state that could get destroyed before the scene
		auto& loadingSceneChildren =  m_loadingScene.GetChildren();
		while (loadingSceneChildren.size()) {
			delete loadingSceneChildren.front();
		}
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
				if (m_scene.load()) {
					m_scene.load()->draw(m_window, sf::RenderStates::Default, t.restart().asSeconds());
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
				/*
				 * TODO unhandled events:
				 * Resized,                ///< The window was resized (data in event.size)
				 * TextEntered,            ///< A character was entered (data in event.text)
				 * MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
				 * MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
				 *
				 * imer: MouseEntered & MouseLeft seem kinda unneeded to me, focus is the important part
				 * MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
				 * MouseLeft,              ///< The mouse cursor left the area of the window (no data)
				 *
				 * JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
				 * JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
				 * JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
				 * JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
				 * JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)
				 *
				 * TouchBegan,             ///< A touch event began (data in event.touch)
				 * TouchMoved,             ///< A touch moved (data in event.touch)
				 * TouchEnded,             ///< A touch event ended (data in event.touch)
				 *
				 * SensorChanged,          ///< A sensor value changed (data in event.sensor)
				 */
				if (event.type == sf::Event::Closed) {
					m_window.close();
					m_running = false;
				} else if (event.type == sf::Event::LostFocus) {
					m_focus = false;
				} else if (event.type == sf::Event::GainedFocus) {
					m_focus = true;
				} else if (m_focus) {
					// Don't handle input events if we're not in focus

					if (event.type == sf::Event::KeyPressed) {
						OnKeyPress.Fire(m_scene, event.key, true);
					} else if (event.type == sf::Event::KeyReleased) {
						// try to give the handler for the down event the up event as well
						if (OnKeyPress.GetLastHandler() &&
								OnKeyPress.GetLastHandler()->CanHandle(event.key, false) &&
								OnKeyPress.GetLastHandler()->handle(event.key, false)) {
							continue;
						}
						OnKeyPress.Fire(m_scene, event.key, false);
					} else if (event.type == sf::Event::MouseButtonPressed) {
						OnMouseClick.Fire(m_scene, event.mouseButton, true);
					} else if (event.type == sf::Event::MouseButtonReleased) {
						// try to give the handler for the down event the up event as well
						if (OnMouseClick.GetLastHandler() &&
								OnMouseClick.GetLastHandler()->CanHandle(event.mouseButton, false) &&
								OnMouseClick.GetLastHandler()->handle(event.mouseButton, false)) {
							continue;
						}
						OnMouseClick.Fire(m_scene, event.mouseButton, true);
					} else if (event.type == sf::Event::MouseWheelScrolled) {
						OnMouseScroll.Fire(m_scene, event.mouseWheelScroll);
					}
				}
			}
			m_scene.load()->update(interval);
			OnUpdate();
			if (!m_multithreaded) {
				m_window.clear(sf::Color::White);
				if (m_scene.load()) {
					m_scene.load()->draw(m_window, sf::RenderStates::Default, interval.asSeconds());
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
		return m_scene.load();
	}
}