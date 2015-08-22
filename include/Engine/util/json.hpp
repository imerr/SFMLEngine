//
// Created by iMer on 22.08.2015.
//

#ifndef ENGINE_UTIL_JSON_HPP
#define ENGINE_UTIL_JSON_HPP

#include <SFML/Graphics/Rect.hpp>
#include <json/value.h>

template <class T>
sf::Rect<T> rectFromJson(Json::Value &node);

template <>
sf::Rect<int> rectFromJson<int>(Json::Value &node) {
	sf::IntRect rect;
	if (node.isArray()) {
		rect.left = node[0u].asInt();
		rect.top = node[1u].asInt();
		rect.width = node[2u].asInt();
		rect.height = node[3u].asInt();
	} else if (node.isObject()) {
		rect.left = node.get("left", 0).asInt();
		rect.top = node.get("top", 0).asInt();
		rect.width = node.get("width", 0).asInt();
		rect.height = node.get("height", 0).asInt();
	}
	return rect;
}

#endif //ENGINE_UTIL_JSON_HPP
