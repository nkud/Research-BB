/*
 * =====================================================================================
 *
 *       Filename:  NormalVirus.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __NORMAL_VIRUS
#define __NORMAL_VIRUS

#include "VirusStrategy.h"

class Tag;
class Virus;
class __SearchStrategy;

/*
 * =====================================================================================
 *        Class:  Normal
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

#endif
