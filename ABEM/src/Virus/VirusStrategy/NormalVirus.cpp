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
#include <stdlib.h>

#include "NormalVirus.h"
#include "VirusStrategy.h"
#include "Tag.h"
#include "Virus.h"
#include "Function.h"

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

void Normal :: check ( int vlen ) const {
  return;
}

