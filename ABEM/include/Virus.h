/*
 * =====================================================================================
 *
 *       Filename:  Virus.h
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___VIRUS
#define ___VIRUS

#include "Gene.h"

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  ウイルス
 * =====================================================================================
 */
class Virus : public Life
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    Virus( Virus & );

    // Virus( __SearchStrategy * );                                     /* コンストラクタ: 戦略 */
    Virus( int );                                                    /* コンストラクタ: タグ長, 戦略 */
    Virus( const char * );                                           /* コンストラクタ: タグ長, 戦略 */

    virtual ~Virus();                                                /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    double getRate() const;                                          /* 感染確率を返す */
    void setRate( const double r );                                  /* 感染確率を設定 */

    int searchStartPoint( Gene & );                                  /* タグに取り付く位置を返す */
    // __SEARCH__TYPE__ getSearchType() const;                          /* サーチ戦略を返す */

//    double value() const;
    int getIncubationPeriod() const;
    int getLethalPeriod() const;
    int getInfectionRate() const;
    int getMutationRate() const;
    /*-----------------------------------------------------------------------------
     *  状態
     *-----------------------------------------------------------------------------*/
    bool isInfectiousPeriod() const;                                 /* 感染性期間 */
    bool isNonInfectiousPeriod() const;                              /* 非感染性期間 */
    bool isLethalPeriod() const;
    /*-----------------------------------------------------------------------------
     *  ウイルス操作
     *-----------------------------------------------------------------------------*/
    bool isEqualTo( const Virus& ) const;                            /* ウイルスのタグが等しいかどうか */

    int getInfectionTime() const { return infection_age_; }          /* 感染期間を返す */
    void incrementInfectionTime() { infection_age_++; }              /* 感染期間を増やす */
    int getClingPoint() const { return cling_point_; }               /* 取り付く位置を返す */
    void setClingPoint( int cp ) { cling_point_ = cp; }              /* 取り付く位置を設定する */
    /*-----------------------------------------------------------------------------
     *  突然変異
     *-----------------------------------------------------------------------------*/
    void mutation( double prob=100 );                                /* 突然変異を起こす */

    bool operator<(const Virus& other) const {
      if( value() < other.value() ) return true; else return false;
    }
    bool operator==(const Virus& other) const {
      if( getLen() != other.getLen() ) {
        return false;
      }
      FOR( i, getLen() ) {
        if( tagAt(i) != other.tagAt(i) ) { return false; }
      }
      return true;
    }
  private:
    double rate_;                                                    /* 感染確率 */

    int cling_point_;                                                /* 取り付いている位置 */
    int infection_age_;                                              /* 感染期間 */
};
#endif
