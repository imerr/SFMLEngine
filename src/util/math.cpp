//
// Created by iMer on 22.08.2015.
//

#include <Engine/util/math.hpp>
namespace engine {
	namespace util {
		float b2AngleDeg(b2Vec2 from, b2Vec2 to) {
			to-=from;
			float a =  atan2f(to.y, to.x) * 180 / fPI;
			if (a < 0) a += 360;
			return a;
		}
	}
}
