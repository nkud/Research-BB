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
 *        Class:  __RandomInterface
 *  Description:  
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

///
/// メルセンヌ・ツイスタ
class __MersenneTwister : public __RandomStrategy {
  public:
    std::mt19937& getMT() {
      if ( mt == NULL ) {
        std::random_device rd;
        mt = new std::mt19937(rd());
      }
      return *mt;
    }
    int randomInt() { return (getMT())(); }

    // double randomDouble();
    int uniformInt( int min, int max ) {
      std::uniform_int_distribution<int> _random(min,max);
      return _random(getMT());
    }
    double uniformDouble( double min, double max ) {
      std::uniform_real_distribution<double> _random(min,max);
      return _random(getMT());
    }
  private:
    std::mt19937 *mt;
};

class Random {
  public:
    static Random& Instance() { 
      static Random singleton;
      if ( singleton.getRandomStrategy() == NULL ) {
        singleton.setRandomStrategy( new __MersenneTwister );
      }
      return singleton;
    }
    void setRandomStrategy( __RandomStrategy *rs ) {
      random_strategy_ = rs;
    }

    int randomInt() { return random_strategy_->randomInt(); }
    // double randomDouble() { return random_strategy_->randomDouble(); }
    int uniformInt( int min, int max ) {
      return random_strategy_->uniformInt( min, max );
    }
    double uniformDouble( double min, double max ) {
      return random_strategy_->uniformDouble( min, max );
    }

    bool probability( double prob );
    int randArray( const int n );
    int randBinary();
    bool randBool();
    int randSign();

    std::string getStrategyName();                           /* 戦略名を取得 */
    const __RandomStrategy* getRandomStrategy() const { return random_strategy_; }
  private:
    // __Random();   
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
