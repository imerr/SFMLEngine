#ifndef ENGINE_UTIL_MATH_HPP
#define ENGINE_UTIL_MATH_HPP

#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

namespace engine {
    namespace util {
        const float fPI = 3.141592654f;

        float b2AngleDeg(b2Vec2 from, b2Vec2 to);

    }
    inline bool floatEqual(float a, float b, float epsilon) {
        return fabsf(a - b) < epsilon;
    }
    inline bool floatEqual(const b2Vec2& a, const b2Vec2& b, float epsilon) {
        return floatEqual(a.x, b.x, epsilon) && floatEqual(a.y, b.y, epsilon);
    }
    inline float b2Angle(b2Vec2 from, b2Vec2 to) {
        to-=from;
        return atan2f(to.y, to.x);
    }

	inline float b2Angle(sf::Vector2f from, sf::Vector2f to) {
		to-=from;
		return atan2f(to.y, to.x);
	}
}

#endif	/* MATH_HPP */

