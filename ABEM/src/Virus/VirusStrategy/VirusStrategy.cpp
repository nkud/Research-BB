/*
 * =====================================================================================
 *
 *       Filename:  VirusStrategy.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "VirusStrategy.h"
#include "Global.h"
#include "Virus.h"
#include "Function.h"
#include "Tag.h"

/*--------------------------------------------------------------------------------------
 *      Method:  Normal :: searchStartPoint( const Tag &, const Tag & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Normal :: searchStartPoint( const Virus &myself, const Tag &tag ) const {
  int sp = -1;                                                       /* 取り付く位置 */
  sp                                                                 /* 取り付く位置を計算する */
    = min_ham_distance_point( tag.getTag(), myself.getTag()->getTag(), tag.getLen(), myself.getTag()->getLen() );
  return sp;                                                         /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Normal :: getSearchType() const {
  return __NORMAL__;                                                 /* 通常ウイルスであることを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Fixed :: searchStartPoint( const Tag &, const Tag & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Fixed :: searchStartPoint( const Virus &myself, const Tag &tag ) const {
  return sp_;                                                        /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Fixed :: getSearchType() const {
  return __FIXED__;                                                  /* 固定ウイルスであることを返す */
}

void Normal :: check ( int vlen ) const {
  return;
}

void Fixed :: check( int vlen ) const {
  assert( vlen+sp_ <= A_DEFAULT_LEN );
}
