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

#include "Function.h"

#include <random>
#include <string>

#include <random>
#include <cstdlib>

class Random;
class __RandomStrategy;
class __MersenneTwister;


/*
 * =====================================================================================
 *        Class:  __RandomStrategy
 *  Description:  乱数生成器の戦略, 純粋仮想関数
 * =====================================================================================
 */
class __RandomStrategy {
  public:
    // virtual double randomDouble();
    virtual int randomInt() = 0;
    virtual int uniformInt( int min, int max ) = 0;
    virtual double uniformDouble( double min, double mas ) = 0;
  private:
};

/*
 * =====================================================================================
 *        Class:  __MersenneTwister
 *  Description:  メルセンヌ・ツイスタ法を使用した戦略
 * =====================================================================================
 */
class __MersenneTwister : public __RandomStrategy {
  public:
    std::mt19937& getMT() {                                          /* 乱数生成関数を作成 */
      if ( mt == NULL ) {
        std::random_device rd;
        mt = new std::mt19937(rd());
      }
      return *mt;
    }
    int randomInt() { return (getMT())(); }                          /* 乱数生成 */

    // double randomDouble();
    int uniformInt( int min, int max ) {                             /* min~maxの乱数を生成 */
      std::uniform_int_distribution<int> _random(min,max);
      return _random(getMT());
    }
    double uniformDouble( double min, double max ) {                 /* min~maxの乱数を生成 */
      std::uniform_real_distribution<double> _random(min,max);
      return _random(getMT());
    }
  private:
    std::mt19937 *mt;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief 線形合同法を用いた乱数生成戦略クラス
/// @date 日時
/// @note メモ
/// @todo コンストラクタ周りを整理する
class __LinearCongruentialGenerator : public __RandomStrategy {
public:
  double randomDouble() {
    static int x = 10;
    int a=1103515245, b=12345, c=2147483647;
    x = (a*x + b)&c;

    return ((double)x+1.0) / ((double)c+2.0);
  }
private:
};

////////////////////////////////////////////////////////////////////////////////
/// @brief standard library
/// @todo 動作確認
class __Standard : public __RandomStrategy {
public:
  double randomDouble() { return ((double)rand()+1.0)/((double)RAND_MAX+2.0); }
  int randomInt() {
    return rand();
  }
  int uniformInt( int min, int max ) {
    int ret = rand()%( max - min + 1 ) + min;
    return ret;
  }
  double uniformDouble( double min, double max ) {
    return uniformInt(min, max-1) + randomDouble();
  }
  __Standard() {
    srand((unsigned)time(NULL));
  }
private:
};

/*
 * =====================================================================================
 *        Class:  Random
 *  Description:  乱数生成クラス
 * =====================================================================================
 */
class Random {
  public:
    int randomInt() { return random_strategy_->randomInt(); }        /* 乱数を生成 */
    // double randomDouble() { return random_strategy_->randomDouble(); }
    int uniformInt( int min, int max ) {
      return random_strategy_->uniformInt( min, max );
    }
    double uniformDouble( double min, double max ) {
      return random_strategy_->uniformDouble( min, max );
    }

    const __RandomStrategy* getRandomStrategy() const { return random_strategy_; }
    void setRandomStrategy( __RandomStrategy *rs ) { random_strategy_ = rs; }

    static Random& Instance() { 
      static Random singleton;
      if ( singleton.getRandomStrategy() == NULL ) {
        singleton.setRandomStrategy( new __MersenneTwister );        /* メルセンヌ・ツイスタを使用 */
      }
      return singleton;
    }
  private:
     Random() {}
    __RandomStrategy *random_strategy_;
};

#endif
