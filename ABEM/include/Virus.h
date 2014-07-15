/* file name  : include/Virus.h
 * authors    : Naoki Ueda
 * created    : Tue Jul 15 18:59:03 2014
 * copyright  : Naoki Ueda
 *
 * modifications:
 *
 */

#ifndef ___VIRUS
#define ___VIRUS

#include "Gene.h"

/** 
 * ウイルスのインターフェイス
 */
class __VirusInterface : public Life {
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    __VirusInterface( __VirusInterface &origin );

    // __VirusInterface( __SearchStrategy * );                                     /* コンストラクタ: 戦略 */
    __VirusInterface( int );                                                    /* コンストラクタ: タグ長, 戦略 */
    __VirusInterface( const char * );                                           /* コンストラクタ: タグ長, 戦略 */

    virtual ~__VirusInterface();                                                /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    virtual int getInfectiousPeriod() const;
    virtual int getNonInfectiousPeriod() const;
    virtual int getLethalPeriod() const;
    virtual int getMutationRate() const;
    virtual double getRate() const;

    void setRate( const double r );                                  /* 感染確率を設定 */

    int searchStartPoint( Gene & );                                  /* タグに取り付く位置を返す */
    // __SEARCH__TYPE__ getSearchType() const;                          /* サーチ戦略を返す */

//    double value() const;
    /*-----------------------------------------------------------------------------
     *  状態
     *-----------------------------------------------------------------------------*/
    bool isInfectiousPeriod() const;                                 /* 感染性期間 */
    bool isNonInfectiousPeriod() const;                              /* 非感染性期間 */
    bool isLethalPeriod() const;
    /*-----------------------------------------------------------------------------
     *  ウイルス操作
     *-----------------------------------------------------------------------------*/
    bool isEqualTo( const __VirusInterface& ) const;                            /* ウイルスのタグが等しいかどうか */

    int getInfectionTime() const { return infection_age_; }          /* 感染期間を返す */
    void incrementInfectionTime() { infection_age_++; }              /* 感染期間を増やす */
    int getClingPoint() const { return cling_point_; }               /* 取り付く位置を返す */
    void setClingPoint( int cp ) { cling_point_ = cp; }              /* 取り付く位置を設定する */
    /*-----------------------------------------------------------------------------
     *  突然変異
     *-----------------------------------------------------------------------------*/
    void mutation( double prob=100 );                                /* 突然変異を起こす */

    bool operator<(const __VirusInterface& other) const {
      if( value() < other.value() ) return true; else return false;
    }
    bool operator==(const __VirusInterface& other) const {
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

/** 
 * ウイルスのインターフェイス 
 */
class NormalVirus : public __VirusInterface
{
  public:
    NormalVirus( const char *tag ) : __VirusInterface(tag) {}

    double getRate() const { return 0; }
//    int getInfectiousPeriod() const;
//    int getNonInfectiousPeriod() const;
//    int getLethalPeriod() const;
//    int getMutationRate() const;
  private:
};

/** 
 * 区分ウイルス
 */
//class SectionedVirus : public __VirusInterface {
// public:
//   double getRate() const { return 0; }                              /* 感染確率を返す */
//   int getInfectiousPeriod() const;
//   int getNonInfectiousPeriod() const;
//   int getLethalPeriod() const;
//   int getMutationRate() const;
// private:
//};
#endif
