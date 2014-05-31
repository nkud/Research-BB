/*
 * =====================================================================================
 *
 *       Filename:  NormalVirus.cpp
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "NormalVirus.h"
#include "SearchStrategy.h"
#include "Tag.h"
#include "Virus.h"
#include "Function.h"

#include <stdlib.h>

/*--------------------------------------------------------------------------------------
 *      Method:  Normal :: searchStartPoint( const Gene &, const Gene & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Normal :: searchStartPoint( const Virus &myself, const Gene &tag ) const {
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

void Normal :: check ( int vlen ) const {
  return;
}

