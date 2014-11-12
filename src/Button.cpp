/* 
 * File:   Button.cpp
 * Author: iMer
 * 
 * Created on 23. August 2014, 07:57
 */

#include "Button.hpp"
#include "SpriteNode.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include <iostream>
namespace engine {

    Button::Button(Scene* scene) : SpriteNode(scene), m_state(BUTTON_NONE) {
		OnClick = [](Button*, sf::Vector2f){};
    }

    Button::~Button() {
    }

    void Button::OnUpdate(sf::Time interval) {

        if (sf::FloatRect(GetGlobalPosition(), m_size).contains(m_scene->GetGame()->GetMousePosition().x, m_scene->GetGame()->GetMousePosition().y)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (m_state != BUTTON_ACTIVE) {
                    m_state = BUTTON_ACTIVE;
                    PlayAnimation("active");
                }
            } else if (m_state == BUTTON_ACTIVE) {
                OnClick(this, m_scene->GetGame()->GetMousePosition());
                PlayAnimation("hover");
                m_state = BUTTON_HOVER;
            } else if (m_state != BUTTON_HOVER) {
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