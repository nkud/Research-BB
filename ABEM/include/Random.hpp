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

class Random {
public:
	Random& Instance() {
		if ( instance_ == NULL )
		{
			instance_ = new Random();
		}
		return *instance_;
	}
	int randomInt();
	double randomDouble();
	int uniformInt();
	double uniformDouble();
private:
	Random() {}
	Random *instance_;
};

#endif