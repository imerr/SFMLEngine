/*
 * File:   Random.hpp
 * Author: iMer
 *
 * Created on 22. August 2014, 22:57
 */

#ifndef UTIL_RANDOM_HPP
#define    UTIL_RANDOM_HPP

#include <random>

namespace engine {
namespace util {

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
}
}


#endif	/* RANDOM_HPP */

