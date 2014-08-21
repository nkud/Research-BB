#ifndef ___TERM_HPP
#define ___TERM_HPP

class Term
{
  public:
    static Term& Instance();                                         /* インスタンス */

    int getMaxTerm();                                                /* 最大実行期間 */
    void setMaxTerm( int t );
    int getTerm();

    bool isHumanInterval();                                          // ヒト期間 
    bool isImmuneInterval();                                         // 免疫機構期間 
    void setHumanInterval( int t );
    void setImmuneInterval( int t );
//    void setInterval( int it, int ht );


    int incrementTerm();

    bool loop();
  private:
    Term();
    int term_;
    int max_term_;

    int human_interval_;                                             // ヒトの間隔 
    int immune_interval_;                                            // 免疫機構の間隔 
};
#endif
