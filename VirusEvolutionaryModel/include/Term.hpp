#ifndef ___TERM_HPP
#define ___TERM_HPP

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

    int incrementTerm();
    bool isInterval( int t ) const;

    bool loop();                                 ///< 期間を進めて、真偽値を返す
  private:
    Term();
    int term_;
    int max_term_;
};
#endif
