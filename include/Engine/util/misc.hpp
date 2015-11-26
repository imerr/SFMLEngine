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
    template <typename T>
    struct AABBQuery: public b2QueryCallback {
        T m_func;
        AABBQuery(T func) : m_func(func) {
        }

        virtual bool ReportFixture(b2Fixture* fixture) {
            return m_func(fixture);
        }
    };
    template <typename T>
    AABBQuery<T> MakeAABBQueryCallback(T func) {
        return AABBQuery<T>(func);
    }

    template <typename T>
    struct RayCastCallback: public b2RayCastCallback {
        T m_func;
        RayCastCallback(T func) : m_func(func) {
        }

        virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                   const b2Vec2& normal, float32 fraction) {
            return m_func(fixture, point, normal, fraction);
        }
    };
    template <typename T>
    RayCastCallback<T> MakeRayCastCallback(T func) {
        return RayCastCallback<T>(func);
    }
}
#endif	/* ENGINE_UTIL_MISC_HPP */

