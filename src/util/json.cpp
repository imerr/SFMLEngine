#include <Engine/util/json.hpp>

namespace engine {

	template<>
	float jsonNodeAs<float>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asFloat();
	}

	template<>
	double jsonNodeAs<double>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asDouble();
	}

	template<>
	int jsonNodeAs<int>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asInt();
	}

	template<>
	unsigned int jsonNodeAs<unsigned int>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asUInt();
	}

	template<>
	int64_t jsonNodeAs<int64_t>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asInt64();
	}

	template<>
	uint64_t jsonNodeAs<uint64_t>(const Json::Value& node) {
		if (node.isNull()) {
			return 0;
		}
		return node.asUInt64();
	}

	template<>
	bool jsonNodeAs<bool>(const Json::Value& node) {
		if (node.isNull()) {
			return false;
		}
		return node.asBool();
	}

	template<>
	const char* jsonNodeAs<const char*>(const Json::Value& node) {
		if (node.isNull()) {
			return nullptr;
		}
		return node.asCString();
	}

	template<>
	std::string jsonNodeAs<std::string>(const Json::Value& node) {
		if (node.isNull()) {
			return "";
		}
		return node.asString();
	}

	template<>
	sf::Color jsonNodeAs<sf::Color>(const Json::Value& node) {
		sf::Color c = sf::Color::White;
		if (node.isArray()) {
			c.r = static_cast<uint8_t>(node.get(0u, 255).asUInt());
			c.g = static_cast<uint8_t>(node.get(1u, 255).asUInt());
			c.b = static_cast<uint8_t>(node.get(2u, 255).asUInt());
			c.a = static_cast<uint8_t>(node.get(3u, 255).asUInt());
		} else if (node.isInt()) {
			unsigned int ic = node.asUInt();
			c.r = static_cast<uint8_t>(ic & 0xFF0000 >> 16);
			c.g = static_cast<uint8_t>(ic & 0xFF00 >> 8);
			c.b = static_cast<uint8_t>(ic & 0xFF);
			c.a = static_cast<uint8_t>(ic & 0xFF000000 >> 24);
		}
		return c;
	}
}
