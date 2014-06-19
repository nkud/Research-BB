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

#include "Config.h"
#include "Function.h"
#include "Virus.h"
#include "Gene.h"
#include "VirusCounter.h"

/*-----------------------------------------------------------------------------
 *
 *  パラメータ操作
 *
 *-----------------------------------------------------------------------------*/
bool Virus :: isNonInfectiousPeriod() const {
  /*-----------------------------------------------------------------------------
   *  感染性期間
   *-----------------------------------------------------------------------------*/
  if( getInfectionTime() <= getIncubationPeriod() ) {
    assert( ! isInfectiousPeriod() );
    return true;
  } else {
    return false;
  }
}
bool Virus :: isInfectiousPeriod() const {
  /*-----------------------------------------------------------------------------
   *  非感染性期間
   *-----------------------------------------------------------------------------*/
  if( getInfectionTime() > getIncubationPeriod() ) {
    assert( ! isNonInfectiousPeriod() );
    return true;
  } else {
    return false;
  }
}

bool Virus :: isIncubationPeriod() const {
  if( getInfectionTime() <= getIncubationPeriod() ) {
    return true;
  } else {
    return false;
  }
}
bool Virus :: isCrisisPeriod() const {
  if( getInfectionTime() > getIncubationPeriod() and getInfectionTime() <= getLethalPeriod() ) {                   /* 潜伏期間を過ぎている */
    return true;
  } else {
    return false;
  }
}
bool Virus :: isLethalPeriod() const {
  if( getInfectionTime() > getLethalPeriod() ) {
    return true;
  } else {
    return false;
  }
}

double Virus :: value() const {
  int ret = 0;
  FOR( i, getLen() ) {
    ret += abs( tagAt(i) - 0 );
  }
  return ret;
}

int Virus :: getIncubationPeriod() const {
  return V_INCUBATION_PERIOD;
}
int Virus :: getLethalPeriod() const {
 return V_LETHAL_PERIOD;
// return V_LETHAL_PERIOD - value()/9;
//  return V_LETHAL_PERIOD - value();
}
int Virus :: getMutationRate() const {
  return V_MUTATION_RATE;
}
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
  rate_( INFECTION_RATE ),                                            /* 感染確率は初期設定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
  gene_ = new Gene( str );
}
/* Tag Len */
Virus :: Virus( int l ):
  rate_( INFECTION_RATE ),                                            /* 感染確率を指定 */
  cling_point_( 0 ),
  infection_age_( 0 )
{
  gene_ = new Gene( l );
  gene_->setTagRandom();                                              /* タグをランダムに初期化 */
}
/* Virus */
Virus :: Virus( Virus &origin ) {
  cling_point_ = 0;
  infection_age_ = 0;
  rate_ = origin.getRate();
  gene_ = new Gene( origin.getGene() );
}

/*-----------------------------------------------------------------------------
 *  Virus :: ~Virus()
 *-----------------------------------------------------------------------------*/
Virus :: ~Virus() {
  assert( gene_ != NULL );

  delete gene_;

  gene_ = NULL;
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
void Virus :: mutation() {
  getGene().mutation();
}
void Virus :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getGene().mutation( prob );
    VirusCounter::Instance().countUpMutation();                      /* カウントする */
  }
}
