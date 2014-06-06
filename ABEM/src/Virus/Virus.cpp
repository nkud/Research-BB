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
#include "VirusStrategy.h"
#include "Function.h"
#include "Gene.h"
#include "VirusCounter.h"

/*-----------------------------------------------------------------------------
 *
 *  パラメータ操作
 *
 *-----------------------------------------------------------------------------*/
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

int Virus :: value() const {
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
  // return V_LETHAL_PERIOD;
  return V_LETHAL_PERIOD - value()/9;
}
int Virus :: getMutationRate() const {
  return V_MUTATION_RATE;
}
double Virus :: getRate() const { 
  // return rate_; 
  double rate = 100*1./(1+value()/9);
  return rate;
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
  gene_ = new Gene( V_DEFAULT_LEN );
  gene_->setTagRandom();                                              /* タグをランダムに初期化 */
  sp->check( V_DEFAULT_LEN );
}
Virus :: Virus( const char *str, __SearchStrategy *sp ) :
  rate_( INFECTION_RATE ),                                            /* 感染確率は初期設定 */
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 )
{
  gene_ = new Gene( str );
}
Virus :: Virus( int l, __SearchStrategy *sp ):
  rate_( INFECTION_RATE ),                                            /* 感染確率を指定 */
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 )
{
  gene_ = new Gene( l );
  gene_->setTagRandom();                                              /* タグをランダムに初期化 */

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
  gene_ = new Gene( v->getGene() );
  search_strategy_ = new Normal;
}

/*-----------------------------------------------------------------------------
 *  Virus :: ~Virus()
 *-----------------------------------------------------------------------------*/
Virus :: ~Virus() {
  assert( gene_ != NULL );
  assert( search_strategy_ != NULL );

  delete gene_;
  delete search_strategy_;

  gene_ = NULL;
  search_strategy_ = NULL;
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
int Virus :: searchStartPoint( const Gene &tag ) const {
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
  getGene()->mutation();
}
void Virus :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getGene()->mutation( prob );
    VirusCounter::Instance().countUpMutation();                      /* カウントする */
  }
}
