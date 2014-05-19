/*
 * =====================================================================================
 *
 *       Filename:  Virus.cpp
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstring>

#include "Global.h"
#include "Virus.h"
#include "VirusStrategy.h"
#include "Function.h"
#include "Tag.h"
#include "VirusCounter.h"

/*-----------------------------------------------------------------------------
 *
 *  パラメータ操作
 *
 *-----------------------------------------------------------------------------*/
bool Virus :: isIncubationPeriod() const {
  if( getInfectionTime() <= V_INCUBATION_PERIOD ) {
    return true;
  } else {
    return false;
  }
}
bool Virus :: isCrisisPeriod() const {
  if( getInfectionTime() > V_INCUBATION_PERIOD ) {                   /* 潜伏期間を過ぎている */
    return true;
  } else {
    return false;
  }
}
bool Virus :: isLethalPeriod() const {
  if( getInfectionTime() > V_LETHAL_PERIOD ) {
    return true;
  } else {
    return false;
  }
}

/*-----------------------------------------------------------------------------
 *
 *  コンストラクタ
 *
 *-----------------------------------------------------------------------------*/
Virus :: Virus( __SearchStrategy *sp ) :
  rate_( INFECTION_RATE ),
  search_strategy_( sp ),
  cling_point_( 0 ),
  infection_time_( 0 ) {
  tag_ = new Tag( V_DEFAULT_LEN );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
  sp->check( V_DEFAULT_LEN );
}
Virus :: Virus( const char *str, __SearchStrategy *sp ) :
  rate_( INFECTION_RATE ),                                            /* 感染確率は初期設定 */
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 )
{
  tag_ = new Tag( str );
}
Virus :: Virus( int l, __SearchStrategy *sp ):
  rate_( INFECTION_RATE ),                                            /* 感染確率を指定 */
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 )
{
  tag_ = new Tag( l );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */

  sp->check( l );
}


/*-----------------------------------------------------------------------------
 *  Virus :: Virus( Virus * )
 *      ウイルスをコピーするコンストラクタ
 *-----------------------------------------------------------------------------*/
Virus :: Virus( Virus *v ) {
  cling_point_ = 0;
  infection_time_ = 0;
  rate_ = v->getRate();
  tag_ = new Tag( v->getTag() );
  search_strategy_ = new Normal;
}

/*-----------------------------------------------------------------------------
 *  Virus :: ~Virus()
 *-----------------------------------------------------------------------------*/
Virus :: ~Virus() {
  assert( tag_ != NULL );
  assert( search_strategy_ != NULL );

  delete tag_;
  delete search_strategy_;

  tag_ = NULL;
  search_strategy_ = NULL;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
double Virus :: getRate() const { return rate_; }
void Virus :: setRate( const double r ) { rate_ = r; }

/*-----------------------------------------------------------------------------
 *  Virus :: isEqualTo( Virus & )
 *      ウイルスのタグに等しければ true を返す
 *-----------------------------------------------------------------------------*/
bool Virus :: isEqualTo( const Virus &v ) const {
  int len = getLen();
  if( len != v.getLen() ) {
    return false;
  }
  FOR( i, len ) {
    if( tagAt(i) != v.tagAt(i) ) {
      return false;
    }
  }

  return true;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: searchStartPoint( Tag & )
 * Description:  タグに対して、ハミング距離が最小となる位置に取り付く
 *--------------------------------------------------------------------------------------
 */
int Virus :: searchStartPoint( const Tag &tag ) const {
  return search_strategy_->searchStartPoint( *this, tag );           /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: getSearchType() const
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Virus :: getSearchType() const {
  return search_strategy_->getSearchType();                          /* 戦略の種類を返す */
}

/*-----------------------------------------------------------------------------
 *  Virus :: mutation()
 *      突然変異を起こす
 *-----------------------------------------------------------------------------*/
void Virus :: mutation() {
  getTag()->mutation();
}
void Virus :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getTag()->mutation( prob );
    VirusCounter::Instance().countUpMutation();                      /* カウントする */
  }
}
