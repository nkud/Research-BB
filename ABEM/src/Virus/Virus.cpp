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
#include "Virus.h"
#include "Gene.h"
#include "VirusCounter.h"

/**
 * 非感染性期間かどうか
 */
bool Virus :: isNonInfectiousPeriod() const {
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
bool Virus :: isInfectiousPeriod() const {
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
bool Virus :: isLethalPeriod() const {
  if( getInfectionTime() > getLethalPeriod() ) {
    return true;
  } else {
    return false;
  }
}

/**
 * 感染性期間を返す
 */
int Virus :: getInfectiousPeriod() const {
  return V_INFECTIOUS_PERIOD;
}
/**
 * 非感染性期間を返す
 */
int Virus :: getNonInfectiousPeriod() const {
  return V_NONINFECTIOUS_PERIOD;
}
/**
 * 致死期間を返す
 */
int Virus :: getLethalPeriod() const {
 return getInfectiousPeriod() + getNonInfectiousPeriod();
}
/**
 * 突然変異率を返す
 */
int Virus :: getMutationRate() const {
  return V_MUTATION_RATE;
}
/**
 * 感染率を返す
 */
double Virus :: getRate() const { 
  // return rate_; 
  double rate = 100*1./(1+value()/9.);
  // LOG(rate)
  // double rate = 50.*((108-value())/108.);
// double rate = 30;
  return rate;
}

/*-----------------------------------------------------------------------------
 *
 *  コンストラクタ
 *
 *-----------------------------------------------------------------------------*/
/* Tag */
Virus :: Virus( const char *str ) :
  Life( str ),
  rate_( INFECTION_RATE ),                                            /* 感染確率は初期設定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
}
/* Tag Len */
Virus :: Virus( int l ):
  Life( l ),
  rate_( INFECTION_RATE ),                                            /* 感染確率を指定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
  getGene().setTagRandom();                                              /* タグをランダムに初期化 */
}
/* Virus */
Virus :: Virus( Virus &origin ) :
  Life( origin.getGene() )
{
  cling_point_ = 0;
  infection_age_ = 0;
  rate_ = origin.getRate();
}


/*-----------------------------------------------------------------------------
 *  Virus :: ~Virus()
 *-----------------------------------------------------------------------------*/
Virus :: ~Virus() {
}

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */

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
 *      Method:  Virus :: searchStartPoint( Gene & )
 * Description:  タグに対して、ハミング距離が最小となる位置に取り付く
 *--------------------------------------------------------------------------------------
 */
int Virus :: searchStartPoint( Gene &gene ) {
  int sp = -1;
  sp = gene.pointOfMinHamDistance( getGene() );
  return sp;
  // return search_strategy_->searchStartPoint( *this, tag );           /* 取り付く位置を返す */
}

/*-----------------------------------------------------------------------------
 *  Virus :: mutation()
 *      突然変異を起こす
 *-----------------------------------------------------------------------------*/
//void Virus :: mutation() {
//  getGene().mutation();
//}
void Virus :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getGene().mutation( prob );
    VirusCounter::Instance().countUpMutation();                      /* カウントする */
  }
}
