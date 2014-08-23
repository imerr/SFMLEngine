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

    Button::Button(Scene* scene) : SpriteNode::SpriteNode(scene), m_state(BUTTON_NONE) {

    }

    Button::~Button() {
    }

    void Button::OnUpdate(sf::Time interval) {
        
        if (sf::FloatRect(GetGlobalPosition(), m_size).contains(m_scene->GetGame()->GetMousePosition().x, m_scene->GetGame()->GetMousePosition().y)) {
            std::cout << "Contains" << std::endl;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                m_state = BUTTON_ACTIVE;
                std::cout << "Active" << std::endl;
                PlayAnimation("active");
            } else if (m_state == BUTTON_ACTIVE) {
                OnClick(m_scene->GetGame()->GetMousePosition());
                std::cout << "CLICK -> HOVER" << std::endl;
                PlayAnimation("hover");
                m_state = BUTTON_HOVER;
            } else {
                std::cout << "HOVER" << std::endl;
                m_state = BUTTON_HOVER;
                PlayAnimation("hover");
            }
        } else if (m_state != BUTTON_NONE) {
            m_state = BUTTON_NONE;
            std::cout << "NONE" << std::endl;
            PlayAnimation("default");
        } else {
            std::cout << "(" << GetGlobalPosition().x << ", " << GetGlobalPosition().y << ", " << m_size.x << ", " << m_size.y << ") doesnt contain (" << m_scene->GetGame()->GetMousePosition().x << ", " << m_scene->GetGame()->GetMousePosition().y << ")" << std::endl;
        }
    }

    void Button::OnClick(sf::Vector2f point) {
        std::cout << "Click" << std::endl;
    }
    uint8_t Button::GetType() const{
        return NT_BUTTON;
    }
}