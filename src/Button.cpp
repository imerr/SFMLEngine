/* 
 * File:   Button.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 07:57
 */

#include "Button.hpp"
#include "Scene.hpp"
#include "Game.hpp"

namespace engine {

	Button::Button(Scene* scene) : SpriteNode(scene), m_state(BUTTON_NONE) {
		m_clickHandler = m_scene->GetGame()->OnMouseClick.MakeHandler(
				[this](const sf::Mouse::Button& button, const sf::Vector2f& position, bool down) -> bool {
					return IsActive() && button == sf::Mouse::Left && (IsMouseIn() || m_state == BUTTON_ACTIVE);
				}, [this](const sf::Mouse::Button& button, const sf::Vector2f& position, bool down) -> bool {
					bool in = IsMouseIn();
					if (m_state != BUTTON_ACTIVE && in) {
						m_state = BUTTON_ACTIVE;
						PlayAnimation("active");
					}
					if (!down) {
						m_state = BUTTON_HOVER;
						PlayAnimation("hover");
						if (in) {
							OnClick.Fire(this, m_scene->GetGame()->GetMousePosition());
						}
					}
					return true;
				}, this);
	}

	Button::~Button() {
	}

	bool Button::IsMouseIn() {
		return sf::FloatRect(GetGlobalPosition() - getOrigin(), m_size).contains(
				m_scene->GetGame()->GetMousePosition().x,
				m_scene->GetGame()->GetMousePosition().y
		);
	}

	void Button::OnUpdate(sf::Time interval) {
		if (IsMouseIn()) {
			if (m_state != BUTTON_HOVER && m_state != BUTTON_ACTIVE) {
				m_state = BUTTON_HOVER;
				PlayAnimation("hover");
			}
		} else if (m_state != BUTTON_NONE) {
			m_state = BUTTON_NONE;
			PlayAnimation("default");
		}
	}

	uint8_t Button::GetType() const {
		return NT_BUTTON;
	}
}