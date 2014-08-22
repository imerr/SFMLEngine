/* 
 * File:   Random.hpp
 * Author: iMer
 *
 * Created on 22. August 2014, 22:57
 */

#ifndef UTIL_RANDOM_HPP
#define	UTIL_RANDOM_HPP
namespace engine {
    namespace util {

        class RandomFloat {
            std::random_device rd;
            std::ranlux48 gen;
            std::uniform_real_distribution<> dis;
        public:
            RandomFloat(float min, float max): gen(rd()), dis(min, max){
                gen.seed(time(nullptr));
            }
            float operator ()(){
                return dis(gen);
            }
        };
    }
}


#endif	/* RANDOM_HPP */

