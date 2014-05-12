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

class __SearchStrategy;

/*-----------------------------------------------------------------------------
 *  ラベル
 *-----------------------------------------------------------------------------*/
enum __SEARCH__TYPE__ {                                              /* 取り付く位置の戦略 */
  __NORMAL__,                                                        /* 通常方式 */
  __FIXED__                                                          /* 固定方式 */
};
// XXX
enum __CLING_POS__ {                                                 /* 取り付く位置 */
  __LEFT__,                                                          /* 取り付く位置：左 */
  __RIGHT__                                                          /* 取り付く位置：右 */
};
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
     *  コンストラクタ
     *-----------------------------------------------------------------------------*/
    Virus( const char * );                                           /* コンストラクタ: タグ */
    Virus( int, double );                                            /* コンストラクタ: タグ長, 感染率 */
    Virus();                                                         /* コンストラクタ: default */

    Virus( __SearchStrategy * );                                     /* コンストラクタ: 戦略 */
    Virus( int, __SearchStrategy * );                                /* コンストラクタ: タグ長, 戦略 */
    Virus( const char *, __SearchStrategy * );                       /* コンストラクタ: タグ長, 戦略 */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    double getRate() const;                                          /* 感染確率を返す */
    void setRate( const double r );                                  /* 感染確率を設定 */

    int searchStartPoint( const Tag & ) const;                       /* タグに取り付く位置を返す */
    __SEARCH__TYPE__ getSearchType() const;


    /*-----------------------------------------------------------------------------
     *  タグ操作
     *-----------------------------------------------------------------------------*/
    Tag* getTag() const { return tag_; }                             /* タグを返す */
    int getLen() const { return tag_->getLen(); }                    /* タグ長を返す */
    tag_t tagAt(int n) const { return tag_->tagAt(n); }              /* 特定位置のタグを返す */

  private:
    Tag *tag_;                                                       /* 電子タグ */
    double rate_;                                                    /* 感染確率 */
    const __SearchStrategy *search_strategy_;                        /* 取り付く位置の決め方の戦略を格納 */
};

/* =====================================================================================
 *        Class:  __SearchStrategy
 *  Description:  タグに取り付く戦略のインターフェイス
 * ================================================================================== */
class __SearchStrategy {                                             /* インターフェイス */
  public:
    virtual int searchStartPoint( const Virus &, const Tag & ) const = 0;
    /* 取り付く位置を返す */
    virtual __SEARCH__TYPE__ getSearchType() const = 0;              /* 戦略の種類を返す */
    virtual void check( int vlen ) const = 0;
};


/*
 * =====================================================================================
 *        Class:  Normal, Fiexed
 *  Description:  タグに取り付く戦略の実装
 * =====================================================================================
 */
class Normal : public __SearchStrategy {                             /* 通常方式 */
  // 最小ハミング距離の位置に取り付く
  public:
    virtual int searchStartPoint( const Virus &myself, const Tag &tag ) const;
    /* 取り付く位置を返す */
    virtual __SEARCH__TYPE__ getSearchType() const;                  /* 戦略の種類を返す: __NORMAL__*/
    virtual void check( int vlen ) const;                            /* ウイルスの長さでエラーチェック*/
};

class Fixed : public __SearchStrategy {                              /* 固定方式 */
  // 初期設定で指定された位置に取り付く
  public:
    Fixed( int n ) : sp_( n ) { }
    virtual int searchStartPoint( const Virus &, const Tag & ) const;
    /* 取り付く位置を返す */
    virtual __SEARCH__TYPE__ getSearchType() const;                  /* 戦略の種類を返す: __FIXED__ */
    virtual void check( int vlen ) const;
  private:
    int sp_;                                                         /* 取り付く位置 */
};

#endif
