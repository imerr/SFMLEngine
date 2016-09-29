#ifndef ENGINE_SCROLLABLE_HPP
#define ENGINE_SCROLLABLE_HPP


#include <Engine/Node.hpp>
#include <SFML/Window.hpp>

namespace engine {
	extern const float scrollSpeedMultiplier;
	class Scrollable: public Node {
		struct ScrollHandler: public EventHandler<bool, const sf::Event::MouseWheelScrollEvent&> {
			Scrollable* scrollable;
			ScrollHandler(Scrollable* scrollable);
			virtual bool handle(const sf::Event::MouseWheelScrollEvent&);
			virtual bool CanHandle(const sf::Event::MouseWheelScrollEvent&);
		};
	protected:
		sf::Vector2i m_viewSize;
		sf::Vector2f m_positionOffset;
		ScrollHandler m_scrollHandler;
		bool m_globalEvents;
	public:
		Scrollable(Scene* scene);

		virtual ~Scrollable();

		virtual bool initialize(Json::Value& root);

		void Scroll(float x, float y);

		bool HandleGlobalEvents() {
			return m_globalEvents;
		}
		const sf::Vector2i& GetViewSize() const {
			return m_viewSize;
		}
		void SetViewSize(sf::Vector2i viewSize)  {
			m_viewSize = viewSize;
		}
		const sf::Vector2f& GetPositionOffset() const {
			return m_positionOffset;
		}
		void SetPositionOffset(sf::Vector2f offset)  {
			m_positionOffset = offset;
		}

	protected:
		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);
		virtual void PostDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);

	};
}
#endif //ENGINE_SCROLLABLE_HPP
