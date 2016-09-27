#include "Text.hpp"
#include <iostream>
#include <Engine/util/json.hpp>

namespace engine {
	Text::Text(Scene* scene) : Node(scene), m_align(ALIGN_LEFT) {
	}

	Text::~Text() {
	}

	void Text::SetText(std::string text) {
		m_text.setString(text);
		switch (m_align) {
			case ALIGN_LEFT:
				m_text.setOrigin(0, 0);
				break;
			case ALIGN_RIGHT:
				m_text.setOrigin(m_text.getGlobalBounds().width, 0);
				break;
			case ALIGN_CENTER:
				m_text.setOrigin(m_text.getGlobalBounds().width / 2, 0);
				break;
			default:
				std::cerr << "Unknown alignment (" << m_align << ")" << std::endl;
		}
	}

	void Text::OnDraw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
		target.draw(m_text, states);
	}

	bool Text::initialize(Json::Value& root) {
		if (!Node::initialize(root)) {
			return false;
		}
		auto text = root["text"];
		if (text.isObject()) {
			m_font.loadFromFile(text.get("font", "").asString());
			m_text.setFont(m_font);
			m_text.setCharacterSize(text.get("size", 30).asInt());
			m_text.setColor(jsonNodeAs<sf::Color>(text["color"]));
			auto align = text["align"];
			if (align.isString()) {
				const std::string& a = align.asString();
				if (a == "left") {
					m_align = ALIGN_LEFT;
				} else if (a == "center") {
					m_align = ALIGN_CENTER;
				} else if (a == "right") {
					m_align = ALIGN_RIGHT;
				}
			}
			uint32_t style = 0;
			if (text.get("bold", false).asBool()) {
				style |= sf::Text::Bold;
			}
			if (text.get("italic", false).asBool()) {
				style |= sf::Text::Italic;
			}
			if (text.get("underlined", false).asBool()) {
				style |= sf::Text::Underlined;
			}
			if (text.get("strikethrough", false).asBool()) {
				style |= sf::Text::StrikeThrough;
			}
			m_text.setStyle(style);
			SetText(text.get("text", "").asString());
		}
		return true;
	}
}

