/*
 * =====================================================================================
 *
 *       Filename:  Random.h
 *
 *    Description:  乱数生成クラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___RANDOM
#define ___RANDOM

#include <random>

class Random {
public:
	static Random& Instance() {
		static Random singleton;
		return singleton;
	}

	std::mt19937& getMT() {
		if ( mt == NULL ) {
			std::random_device rd;
			mt = new std::mt19937(rd());
		}
		return *mt;
	}
	int randomInt() {
		return (getMT())();
	}
	double randomDouble();
	int uniformInt( int min, int max ) {
		std::uniform_int_distribution<int> random(min,max);
		return random(getMT());
	}
	double uniformDouble( double min, double max ) {
		std::uniform_real_distribution<double> random(min,max);
		return random(getMT());
	}
private:
	Random() {}

	std::mt19937 *mt;
};

#endif
