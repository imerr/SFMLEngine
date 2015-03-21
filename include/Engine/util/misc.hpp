/*
 * File:   misc.hpp
 * Author: iMer
 *
 * Created on 12. August 2014, 06:17
 */

#ifndef ENGINE_UTIL_MISC_HPP
#define	ENGINE_UTIL_MISC_HPP
namespace engine {
    namespace util {

        template <typename T> T max(T one, T two) {
            return one > two ? one : two;
        };

        template <typename T> T min(T one, T two) {
            return one > two ? two : one;
        };

        template <typename T> T minmax(T min, T value, T max) {
            if (value < min) {
                return min;
            }
            if (value > max) {
                return max;
            }
            return value;
        };
		
    }
}
#endif	/* ENGINE_UTIL_MISC_HPP */

