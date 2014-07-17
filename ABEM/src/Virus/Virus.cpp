/* file name  : src/Virus/Virus.cpp
 * authors    : Naoki Ueda
 * created    : Tue Jul 15 09:35:42 2014
 * copyright  : Naoki Ueda
 *
 * modifications:
 *
 */

#include <cstdlib>
#include <cstring>

#include "Config.h"
#include "Function.h"
#include "VirusInterface.hpp"
#include "Gene.h"
#include "VirusCounter.h"

/**
 * 非感染性期間かどうか
 */
bool __VirusInterface :: isNonInfectiousPeriod() const {
  if( getInfectionTime() <= getNonInfectiousPeriod() ) {             //< 感染期間が非感染性期間以下なら
    assert( ! isInfectiousPeriod() and "感染性期間ではない" );
    return true;                                                     //< 真
  } else {                                                           //< そうでなければ 
    return false;                                                    //< 偽 
  }
}

/**
 * 感染性期間かどうか
 */
bool __VirusInterface :: isInfectiousPeriod() const {
  if( getInfectionTime() > getNonInfectiousPeriod() ) {              //< 感染期間が非感染性期間を超えれば 
    assert( ! isNonInfectiousPeriod() and "非感染性期間ではない" );
    return true;                                                     //< 真 
  } else {                                                           //< そうでなければ 
    return false;                                                    //< 偽 
  }
}

/**
 * 感染性期間を返す
 */
bool __VirusInterface :: isLethalPeriod() const {
  if( getInfectionTime() > getLethalPeriod() ) {
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
/* Tag */
__VirusInterface :: __VirusInterface( const char *str ) :
  Life( str ),
  rate_( INFECTION_RATE ),                                            /* 感染確率は初期設定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
}
/* Tag Len */
__VirusInterface :: __VirusInterface( int l ):
  Life( l ),
  rate_( INFECTION_RATE ),                                            /* 感染確率を指定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
  getGene().setTagRandom();                                              /* タグをランダムに初期化 */
}
/* __VirusInterface */
__VirusInterface :: __VirusInterface( __VirusInterface &origin ) :
  Life( origin.getGene() )
{
  cling_point_ = 0;
  infection_age_ = 0;
  rate_ = origin.getRate();
}



/*-----------------------------------------------------------------------------
 *  __VirusInterface :: ~__VirusInterface()
 *-----------------------------------------------------------------------------*/
__VirusInterface :: ~__VirusInterface() {
}

/*--------------------------------------------------------------------------------------
 *      Method:  __VirusInterface :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */

void __VirusInterface :: setRate( const double r ) { rate_ = r; }

/*-----------------------------------------------------------------------------
 *  __VirusInterface :: isEqualTo( __VirusInterface & )
 *      ウイルスのタグに等しければ true を返す
 *-----------------------------------------------------------------------------*/
bool __VirusInterface :: isEqualTo( const __VirusInterface &v ) const {
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
 *      Method:  __VirusInterface :: searchStartPoint( Gene & )
 * Description:  タグに対して、ハミング距離が最小となる位置に取り付く
 *--------------------------------------------------------------------------------------
 */
int __VirusInterface :: searchStartPoint( Gene &gene ) {
  int sp = -1;
  sp = gene.pointOfMinHamDistance( getGene() );
  return sp;
  // return search_strategy_->searchStartPoint( *this, tag );           /* 取り付く位置を返す */
}

/*-----------------------------------------------------------------------------
 *  __VirusInterface :: mutation()
 *      突然変異を起こす
 *-----------------------------------------------------------------------------*/
//void __VirusInterface :: mutation() {
//  getGene().mutation();
//}
void __VirusInterface :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getGene().mutation( prob );
    VirusCounter::Instance().countUpMutation();                      /* カウントする */
  }
}

int __VirusInterface :: getInfectionTime() const { return infection_age_; }          /* 感染期間を返す */
void __VirusInterface :: incrementInfectionTime() { infection_age_++; }              /* 感染期間を増やす */
int __VirusInterface :: getClingPoint() const { return cling_point_; }               /* 取り付く位置を返す */
void __VirusInterface :: setClingPoint( int cp ) { cling_point_ = cp; }    

bool __VirusInterface :: operator<(const __VirusInterface& other) const {
  if( value() < other.value() ) return true; else return false;
}

bool __VirusInterface :: operator==(const __VirusInterface& other) const {
  if( getLen() != other.getLen() ) {
    return false;
  }
  FOR( i, getLen() ) {
    if( tagAt(i) != other.tagAt(i) ) { return false; }
  }
  return true;
}