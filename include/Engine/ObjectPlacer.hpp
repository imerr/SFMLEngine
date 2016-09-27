#ifndef ENGINE_OBJECTPLACER_HPP
#define ENGINE_OBJECTPLACER_HPP

#include "Node.hpp"
#include <SFML/Window.hpp>

namespace engine {

	/**
	 * Class for placing objects, sort of a level editor thing, but really shitty
	 */
	class ObjectPlacer : public Node {
	public:

		class MouseHandler : public EventHandler<const sf::Event::MouseButtonEvent&> {
		protected:
			ObjectPlacer* m_placer;
		public:
			MouseHandler(ObjectPlacer* placer);

			virtual void handle(const sf::Event::MouseButtonEvent&);
		};

		class KeyHandler : public EventHandler<const sf::Event::KeyEvent&> {
		protected:
			ObjectPlacer* m_placer;
		public:
			KeyHandler(ObjectPlacer* placer);

			virtual void handle(const sf::Event::KeyEvent&);
		};

		class DeleteHandler : public EventHandler<const Node*> {
		protected:
			ObjectPlacer* m_placer;
		public:
			DeleteHandler(ObjectPlacer* placer);

			virtual void handle(const Node*);
		};

	protected:
		std::vector<std::string> m_objects;
		int m_current;
		MouseHandler m_mouseHandler;
		Json::Value m_root;
		Node* m_currentNode;
		KeyHandler m_keyHandler;
		DeleteHandler m_deleteHandler;
		bool m_movement;

	public:
		ObjectPlacer(Scene* scene);

		virtual ~ObjectPlacer();

		void Place(float x, float y);

		void New(float x, float y, bool saveOld = true);

		void Remove();

		void Next() {
			m_current++;
			if (m_current >= m_objects.size()) {
				m_current = 0;
			}
		}

		void Prev() {
			m_current--;
			if (m_current < 0) {
				m_current = m_objects.size() - 1;
			}
		}

		virtual bool initialize(Json::Value& root);

		Node* GetCurrentNode() const {
			return m_currentNode;
		}

		void SetCurrentNode(Node* currentNode) {
			m_currentNode = currentNode;
		}

		void Save();

	protected:
		virtual void OnUpdate(sf::Time interval);
	};
}

#endif	/* ENGINE_OBJECTPLACER_HPP */

