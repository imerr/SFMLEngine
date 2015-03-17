/* 
 * File:   Text.hpp
 * Author: iMer
 *
 * Created on 7. Dezember 2014, 00:48
 */

#ifndef ENGINE_TEXT_HPP
#define	ENGINE_TEXT_HPP
#include "Node.hpp"
#include <SFML/Graphics.hpp>
namespace engine {

    class Text : public Node {
    protected:
        sf::Font m_font;
        sf::Text m_text;
    public:
        Text(Scene* scene);
        virtual ~Text();

        void SetText(std::string text) {
            m_text.setString(text);
        }

        std::string GetText() const {
            m_text.getString();
        }

        sf::Text& GetSFText() {
            return m_text;
        }

        void SetFont(sf::Font font) {
            m_font = font;
        }

        sf::Font GetFont() const {
            return m_font;
        }
        virtual bool initialize(Json::Value& root);

        virtual uint8_t GetType() const {
            return NT_TEXT;
        }


    protected:
        virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta);

    };
}

#endif	/* TEXT_HPP */

