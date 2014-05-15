/*
 * =====================================================================================
 *
 *       Filename:  VirusStrategy.h
 *
 *    Description:  
 *
*         Author:   Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#ifndef ___VIRUS_STRATEGY
#define ___VIRUS_STRATEGY

#include "VirusStrategy/NormalVirus/NormalVirus.h"
#include "VirusStrategy/FixedVirus/FixedVirus.h"

class Tag;
class Virus;

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

#endif
