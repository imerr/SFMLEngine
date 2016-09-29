#ifndef ENGINE_UTIL_JSON_HPP
#define ENGINE_UTIL_JSON_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <json/value.h>
#include <stdint.h>

namespace engine {
	template<class T>
	T jsonNodeAs(const Json::Value& node);

	template<>
	float jsonNodeAs<float>(const Json::Value& node);

	template<>
	double jsonNodeAs<double>(const Json::Value& node);

	template<>
	int jsonNodeAs<int>(const Json::Value& node);

	template<>
	unsigned int jsonNodeAs<unsigned int>(const Json::Value& node);

	template<>
	int64_t jsonNodeAs<int64_t>(const Json::Value& node);

	template<>
	uint64_t jsonNodeAs<uint64_t>(const Json::Value& node);

	template<>
	bool jsonNodeAs<bool>(const Json::Value& node);

	template<>
	const char* jsonNodeAs<const char*>(const Json::Value& node);

	template<>
	std::string jsonNodeAs<std::string>(const Json::Value& node);

	template<>
	sf::Color jsonNodeAs<sf::Color>(const Json::Value& node);


	template<class T>
	sf::Rect<T> rectFromJson(Json::Value& node) {
		sf::Rect<T> rect;
		if (node.isArray()) {
			rect.left = jsonNodeAs<T>(node[0u]);
			rect.top = jsonNodeAs<T>(node[1u]);
			rect.width = jsonNodeAs<T>(node[2u]);
			rect.height = jsonNodeAs<T>(node[3u]);
		} else if (node.isObject()) {
			rect.left = jsonNodeAs<T>(node["left"]);
			rect.top = jsonNodeAs<T>(node["top"]);
			rect.width = jsonNodeAs<T>(node["width"]);
			rect.height = jsonNodeAs<T>(node["height"]);
		}
		return rect;
	}


	template<class T>
	sf::Vector2<T> vector2FromJson(Json::Value& node) {
		sf::Vector2<T> v;
		if (node.isArray()) {
			v.x = jsonNodeAs<T>(node[0u]);
			v.y = jsonNodeAs<T>(node[1u]);
		} else if (node.isObject()) {
			v.x = jsonNodeAs<T>(node["x"]);
			v.y = jsonNodeAs<T>(node["y"]);
		}
		return v;
	}
}

#endif
