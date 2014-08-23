/* 
 * File:   Button.hpp
 * Author: iMer
 *
 * Created on 23. August 2014, 07:57
 */

#ifndef BUTTON_HPP
#define	BUTTON_HPP
#include "SpriteNode.hpp"
namespace engine {

    class Button : public SpriteNode {
    protected:
        uint8_t m_state;
    public:
        enum ButtonStates{
            BUTTON_NONE,
            BUTTON_HOVER,
            BUTTON_ACTIVE,
            BUTTON_STATE_MAX
        };
        Button(Scene* scene);
        virtual ~Button();
        virtual uint8_t GetType() const;
        virtual void OnClick(sf::Vector2f point);
    private:
        virtual void OnUpdate(sf::Time interval);
    };
    
}

#endif	/* BUTTON_HPP */

