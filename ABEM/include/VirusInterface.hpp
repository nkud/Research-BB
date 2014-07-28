#ifndef ___VIRUS_INTERFACE
#define ___VIRUS_INTERFACE

#include "Gene.h"

class Gene;
class Life;

/** 
 * ウイルスのインターフェイス
 */
class __VirusInterface : public Life {
  public:

    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    virtual int getInfectiousPeriod() const = 0;
    virtual int getNonInfectiousPeriod() const = 0;
    virtual int getLethalPeriod() const = 0;
    virtual int getMutationRate() const = 0;
    virtual double getRate() const = 0;
    virtual __VirusInterface& clone() = 0;

    void setRate( const double r );                                  /* 感染確率を設定 */

    int searchStartPoint( Gene & );                                  /* タグに取り付く位置を返す */
    // __SEARCH__TYPE__ getSearchType() const;                          /* サーチ戦略を返す */

  //    double value() const;

    /** 感染性期間 */
    bool isInfectiousPeriod() const;
    /** 非感染性期間 */
    bool isNonInfectiousPeriod() const;
    /** 致死期間 */
    bool isLethalPeriod() const;
    /*-----------------------------------------------------------------------------
     *  ウイルス操作
     *-----------------------------------------------------------------------------*/
    bool isEqualTo( const __VirusInterface& ) const;                            /* ウイルスのタグが等しいかどうか */

    int getInfectionTime() const;          /* 感染期間を返す */
    void incrementInfectionTime();              /* 感染期間を増やす */
    int getClingPoint() const;               /* 取り付く位置を返す */
    void setClingPoint( int cp );              /* 取り付く位置を設定する */
    
    /**
     * 突然変異をさせる。デフォルトでは100％
     * 
     * @param prob
     */
    virtual void mutation( double prob=100 );                                /* 突然変異を起こす */

    /** オペレータ */
    bool operator<(const __VirusInterface& other) const;
    bool operator==(const __VirusInterface& other) const;

    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    __VirusInterface( __VirusInterface &origin );

    // __VirusInterface( __SearchStrategy * );                                     /* コンストラクタ: 戦略 */
    __VirusInterface( int );                                                    /* コンストラクタ: タグ長, 戦略 */
    __VirusInterface( const char * );                                           /* コンストラクタ: タグ長, 戦略 */

    virtual ~__VirusInterface();                                                /* デストラクタ */
  private:
    double rate_;                                                    /* 感染確率 */

    int cling_point_;                                                /* 取り付いている位置 */
    int infection_age_;                                              /* 感染期間 */
};

#endif
