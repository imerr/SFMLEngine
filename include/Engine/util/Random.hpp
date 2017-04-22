#ifndef ENGINE_UTIL_RANDOM_HPP
#define ENGINE_UTIL_RANDOM_HPP

#include <random>
#include <SFML/System/Vector2.hpp>

namespace engine {
	extern std::random_device rd;

	template<typename T = double>
	class RandomFloat {
		std::ranlux48 gen;
		std::uniform_real_distribution<T> dis;
	public:

		RandomFloat(T min, T max) : gen(rd()), dis(min, max) {

		}

		T operator()() {
			return dis(gen);
		}
	};

	template<typename T = int>
	class RandomInt {
		std::ranlux48 gen;
		std::uniform_int_distribution<T> dis;
	public:

		RandomInt(T min, T max) : gen(rd()), dis(min, max) {

		}

		T operator()() {
			return dis(gen);
		}
	};

	template <typename T = float>
	sf::Vector2<T> RandomVector(sf::Vector2<T> min, sf::Vector2<T> max) {
		sf::Vector2<T> result;
		RandomFloat<float> x(min.x, max.x);
		RandomFloat<float> y(min.y, max.y);
		result.x = x();
		result.y = y();
		return result;
	}
}


#endif

