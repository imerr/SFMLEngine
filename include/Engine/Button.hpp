#ifndef ENGINE_BUTTON_HPP
#define ENGINE_BUTTON_HPP

#include "SpriteNode.hpp"

namespace engine {

	class Button : public SpriteNode {
	protected:
		uint8_t m_state;
		BaseEventHandler* m_clickHandler;
	public:
		enum ButtonStates {
			BUTTON_NONE,
			BUTTON_HOVER,
			BUTTON_ACTIVE,
			BUTTON_STATE_MAX
		};

		Button(Scene* scene);

		virtual ~Button();

		virtual uint8_t GetType() const;

		Event<Button*, sf::Vector2f> OnClick;
	protected:
		virtual void OnUpdate(sf::Time interval);

		bool IsMouseIn();
	};

}

#endif

