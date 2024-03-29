#ifndef ___TERM_HPP
#define ___TERM_HPP

#include <iostream>
#include "Benchmark.hpp"

/**
 * @brief 期間管理
 */
class Term
{
  public:
    static Term& Instance();                     ///< インスタンス 

    int getMaxTerm() const;                      ///< 最大実行期間を取得する
    void setMaxTerm( int t );                    ///< 最大実行期間を設定する
    int getTerm() const;                         ///< 現在期間を取得する

    int getRemainingTerm() const;                ///< 残り最大実行期間
    double calcEstimatedRemainingTime();         ///< 残り推定時間を計算

    int incrementTerm();
    bool isInterval( int t ) const;

    bool loop();                                 ///< 期間を進めて、真偽値を返す
  private:
    Term() : prev_time_(0), prev_term_(0) { }

    int term_;
    int max_term_;
    double prev_time_;
    int prev_term_;
};
#endif
