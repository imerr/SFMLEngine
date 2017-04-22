#ifndef ENGINE_GAME_HPP
#define ENGINE_GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Scene.hpp"
#include <atomic>
#include "util/Event.hpp"
#include "LoadingScene.hpp"

namespace engine {

	class Game {
	public:

	protected:
		sf::RenderWindow m_window;
		std::atomic<Scene*> m_scene;
		std::atomic<bool> m_running;
		sf::Clock m_lastLogicUpdate;
		sf::Mutex m_lastLogicUpdateMutex;
		// stats
		std::atomic<int> m_fps;
		int m_tps;
		std::atomic<bool> m_focus;
		std::string m_windowTitle;
		sf::Color m_clearColor;
		LoadingScene m_loadingScene;
		bool m_multithreaded;
	public:
		CancelableEvent<const sf::Event::KeyEvent&, bool> OnKeyPress;
		CancelableEvent<const sf::Mouse::Button&, const sf::Vector2f&, bool> OnMouseClick;
		CancelableEvent<const sf::Event::MouseWheelScrollEvent&> OnMouseScroll;
	public:
		Game(uint32_t width = 1024, uint32_t height = 576, bool multithreaded =
		// TODO(imer): android crashes with a draw thread - still need to debug that
#ifdef SFML_SYSTEM_ANDROID
		false
#else
		true
#endif
		);

		virtual ~Game();

		void run();

		void GraphicLoop();

		void LogicLoop();

		sf::RenderWindow* GetWindow();

		// Helper
		sf::Vector2f GetMousePosition();

		bool IsFocus() const;

		Scene* GetScene() const;

		void SetScene(Scene* scene) {
			m_scene = scene;
		}

		void SwitchScene(Scene* scene) {
			if (!m_scene.load()) {
				m_scene = scene;
				return;
			}
			m_loadingScene.Switch(m_scene, scene);
			m_scene = &m_loadingScene;
		}

		LoadingScene* GetLoadingScene() {
			return &m_loadingScene;
		}

	protected:
		virtual void OnUpdate() {};
	};

}

#endif

