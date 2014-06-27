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
#include <string>

#include <random>


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


// /
// / Random
// class Random {
//   public:
//     static Random& Instance() {
//       static Random singleton;
//       return singleton;
//     }

//     std::mt19937& getMT() {
//       if ( mt == NULL ) {
//         std::random_device rd;
//         mt = new std::mt19937(rd());
//       }
//       return *mt;
//     }
//     int randomInt() {
//       return (getMT())();
//     }
//     double randomDouble();
//     int uniformInt( int min, int max ) {
//       std::uniform_int_distribution<int> random(min,max);
//       return random(getMT());
//     }
//     double uniformDouble( double min, double max ) {
//       std::uniform_real_distribution<double> random(min,max);
//       return random(getMT());
//     }
//   private:
//     Random() {}

//     std::mt19937 *mt;
// };

#endif
