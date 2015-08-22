/* 
 * File:   math.hpp
 * Author: iMer
 *
 * Created on 12. August 2014, 06:54
 */

#ifndef ENGINE_UTIL_MATH_HPP
#define	ENGINE_UTIL_MATH_HPP
namespace engine {
    namespace util {
        const float fPI = 3.141592654f;

		float b2AngleDeg(const b2Vec2& from, b2Vec2 to) {
			to-=from;
			return atan2(to.x, to.y) / 180 * fPI;
		}
    }
}


#endif	/* MATH_HPP */

