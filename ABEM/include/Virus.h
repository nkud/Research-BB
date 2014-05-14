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

#include "Tag.h"
#include "VirusStrategy.h"

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  ウイルス
 * =====================================================================================
 */
class Virus
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    Virus( const char * );                                           /* コンストラクタ: タグ */
    Virus( int, double );                                            /* コンストラクタ: タグ長, 感染率 */
    Virus();                                                         /* コンストラクタ: default */
    Virus( Virus * );

    Virus( __SearchStrategy * );                                     /* コンストラクタ: 戦略 */
    Virus( int, __SearchStrategy * );                                /* コンストラクタ: タグ長, 戦略 */
    Virus( const char *, __SearchStrategy * );                       /* コンストラクタ: タグ長, 戦略 */

    ~Virus();                                                        /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    double getRate() const;                                          /* 感染確率を返す */
    void setRate( const double r );                                  /* 感染確率を設定 */

    int searchStartPoint( const Tag & ) const;                       /* タグに取り付く位置を返す */
    __SEARCH__TYPE__ getSearchType() const;

    bool isEqualTo( Virus & );


    /*-----------------------------------------------------------------------------
     *  タグ操作
     *-----------------------------------------------------------------------------*/
    Tag* getTag() const { return tag_; }                             /* タグを返す */
    int getLen() const { return tag_->getLen(); }                    /* タグ長を返す */
    tag_t tagAt(int n) const { return tag_->tagAt(n); }              /* 特定位置のタグを返す */

    int getInfectionTime() const { return infection_time_; }
    void incrementInfectionTime() { infection_time_++; }
    int getClingPoint() const { return cling_point_; }
    void setClingPoint( int cp ) { cling_point_ = cp; }

  private:
    Tag *tag_;                                                       /* 電子タグ */
    double rate_;                                                    /* 感染確率 */
    const __SearchStrategy *search_strategy_;                        /* 取り付く位置の決め方の戦略を格納 */
    // XXX: -> ClingPointStrategy

    int cling_point_;                                                /* 取り付いている位置 */
    int infection_time_;                                             /* 感染期間 */
};
#endif
