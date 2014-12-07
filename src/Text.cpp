/* 
 * File:   Text.cpp
 * Author: iMer
 * 
 * Created on 7. Dezember 2014, 00:48
 */

#include "Text.hpp"
namespace engine{
	Text::Text(Scene* scene): Node(scene) {
	}

	Text::~Text() {
	}
	
	void Text::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta){
		target.draw(m_text, states);
	}
	bool Text::initialize(Json::Value& root){
		if (!Node::initialize(root)){
			return false;
		}
		auto text = root["text"];
		if (text.isObject()){
			m_font.loadFromFile(text.get("font", "").asString());
			m_text.setFont(m_font);
			m_text.setCharacterSize(text.get("size", 30).asInt());
			auto color = text["color"];
			if (color.isArray()){
				m_text.setColor(sf::Color(color.get(0u, 0).asInt(), color.get(1u, 0).asInt(), color.get(2u, 0).asInt(), color.get(3u, 255).asInt()));
			}
			m_text.setString(text.get("text", "").asString());
			uint32_t style;
			if (text.get("bold", false).asBool()){
				style |= sf::Text::Bold;
			}
			m_text.setStyle(style);
		}
		return true;
	}
}

