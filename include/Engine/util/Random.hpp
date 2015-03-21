/*
 * File:   Random.hpp
 * Author: iMer
 *
 * Created on 22. August 2014, 22:57
 */

#ifndef UTIL_RANDOM_HPP
#define	UTIL_RANDOM_HPP
#include <random>
namespace engine {
    namespace util {

        extern std::random_device rd;

        class RandomFloat {
            std::ranlux48 gen;
            std::uniform_real_distribution<> dis;
        public:

            RandomFloat(double min, double max) : gen(rd()), dis(min, max) {

            }

            double operator()() {
                return dis(gen);
            }
        };
    }
}


#endif	/* RANDOM_HPP */

