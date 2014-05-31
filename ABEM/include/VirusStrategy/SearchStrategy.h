/*
 * =====================================================================================
 *
 *       Filename:  SearchStrategy.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __SEARCH_STRATEGY
#define __SEARCH_STRATEGY

class Gene;
class Virus;

/*-----------------------------------------------------------------------------
 *  ラベル
 *-----------------------------------------------------------------------------*/
enum __SEARCH__TYPE__ {                                              /* 取り付く位置の戦略 */
  __NORMAL__,                                                        /* 通常方式 */
  __FIXED__                                                          /* 固定方式 */
};

/* =====================================================================================
 *        Class:  __SearchStrategy
 *  Description:  タグに取り付く戦略のインターフェイス
 * ================================================================================== */
class __SearchStrategy {                                             /* インターフェイス */
  public:
    virtual ~__SearchStrategy() { };
    virtual int searchStartPoint( const Virus &, const Gene & ) const = 0;
    /* 取り付く位置を返す */
    virtual __SEARCH__TYPE__ getSearchType() const = 0;              /* 戦略の種類を返す */
    virtual void check( int vlen ) const = 0;
};

#endif
