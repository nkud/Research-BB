#ifndef ___TERM_HPP
#define ___TERM_HPP

class Term
{
  public:
    static Term& Instance();

    int getMaxTerm();
    void setMaxTerm( int t );
    int getTerm();

    int isHumanTerm();                                               /* ヒト期間 */
    int isImmuneTerm();                                              /* 免疫機構期間 */

    int incrementTerm();

    bool loop();
  private:
    Term();
    int term_;
    int max_term_;

    int human_interval_;                                             /* ヒトの間隔 */
    int immune_interval_;                                            /* 免疫機構の間隔 */
};
#endif
