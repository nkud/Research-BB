/*
 * =====================================================================================
 *
 *       Filename:  FixedVirus.cpp
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "FixedVirus.h"
#include "VirusStrategy.h"
#include "Tag.h"
#include "Virus.h"

/*--------------------------------------------------------------------------------------
 *      Method:  Fixed :: searchStartPoint( const Tag &, const Tag & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Fixed :: searchStartPoint( const Virus &myself, const Tag &tag ) const {
  return sp_;                                                        /* 取り付く位置を返す */
}

__SEARCH__TYPE__ Fixed :: getSearchType() const {
  return __FIXED__;                                                  /* 固定ウイルスであることを返す */
}

void Fixed :: check( int vlen ) const {
  assert( vlen+sp_ <= A_DEFAULT_LEN );
}
