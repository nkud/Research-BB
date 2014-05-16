/*
 * =====================================================================================
 *
 *       Filename:  FixedVirus.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __FIXED_VIRUS
#define __FIXED_VIRUS

#include "SearchStrategy.h"

class Tag;
class Virus;

/*
 * =====================================================================================
 *        Class:  Fiexed
 *  Description:  タグに取り付く戦略の実装
 * =====================================================================================
 */
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
