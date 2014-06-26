/*
 * =====================================================================================
 *
 *       Filename:  Agent.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include "Agent.h"
#include "AgentStrategy.h"
#include "ImmuneSystem.h"
#include "Function.h"
#include "Gene.h"
#include "AgentCounter.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>


/*-----------------------------------------------------------------------------
 *  isSusceptible()
 *      感受性保持
 *-----------------------------------------------------------------------------*/
bool Agent :: isSusceptible() const {
  return immune_system_->isSusceptible();
}
/*-----------------------------------------------------------------------------
 *  isIncubationPeriod
 *      潜伏期間
 *-----------------------------------------------------------------------------*/
bool Agent :: isIncubationPeriod() const {
  return immune_system_->isIncubationPeriod();
}
/*-----------------------------------------------------------------------------
 *  isSymptomaticPeriod()
 *      症候性期間
 *-----------------------------------------------------------------------------*/
bool Agent :: isSymptomaticPeriod() const {
  return immune_system_->isSymptomaticPeriod();
}
/*-----------------------------------------------------------------------------
 *  isLethal()
 *-----------------------------------------------------------------------------*/
bool Agent :: isLethal() const {
  return immune_system_->isLethal();
}

/*-----------------------------------------------------------------------------
 *  contact( Agent & )
 *      他エージェントが保持する感染力を持ったすべてのウイルスに対して、
 *      そのウイルス固有の感染力に従って待機ウイルスとする。
 *-----------------------------------------------------------------------------*/
void Agent :: contact( Agent &other ) {
  VECTOR(Virus *) crisis_virus = other.getImmuneSystem().getCrisisVirusList(); /*  */
  EACH( it_v, crisis_virus ) {                                       /* すべての感染ウイルスの */
    assert( (**it_v).isInfectiousPeriod() );                         /* 感染性ウイルスでなければエラー */
    if( probability((*it_v)->getRate()) ) {                          /* 感染率に従って */
      getImmuneSystem().pushStandByVirus( **it_v );                   /* 待機ウイルスにする */
      AgentCounter::Instance().countUpContact();                     /* モニタリング */
    }
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: Agent() / ~Agent()
 * Description:  コンストラクタ、デストラクタ
 *               性別はランダムに初期化
 *               寿命は０才から最大年齢までの範囲でランダムに初期化
 *--------------------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 *  移動戦略・子孫戦略・タグ長　指定
 *-----------------------------------------------------------------------------*/
Agent :: Agent(
    __MovingStrategy *ms,                                            /* 移動戦略 */
    int len                                                          /* タグ長 */
    ) :
  Life( len ),
  x_( 0 ),
  y_( 0 ),
  immune_system_( NULL ),
  moving_strategy_( ms )
{
  immune_system_ = new ImmuneSystem;                                 /* 免疫機構実装 */

  getGene().setTagRandom();                                          /* タグをランダムに初期化 */
}

/*-----------------------------------------------------------------------------
 *  移動戦略・子孫戦略・タグ　指定
 *-----------------------------------------------------------------------------*/
Agent :: Agent(
    __MovingStrategy *ms,                                            /* 移動戦略 */
    Gene *gene                                                       /* 電子タグ */
    ) :
  Life( *gene ),
  x_( 0 ),
  y_( 0 ),
  moving_strategy_( ms )
{
  immune_system_ = new ImmuneSystem;                                 /* 免疫機構実装 */

  getGene().setTagRandom();
}
/*-----------------------------------------------------------------------------
 *  移動戦略・子孫戦略・タグ長（最小値~最大値）　指定
 *-----------------------------------------------------------------------------*/
Agent :: Agent( __MovingStrategy *ms, int minl, int maxl ) :
  Life( rand_interval_int(minl, maxl) ),
  x_( 0 ),
  y_( 0 ),
  moving_strategy_( ms )
{
  immune_system_ = new ImmuneSystem();                               /* 免疫機構実装 */

  getGene().setTagRandom();                                          /* タグをランダムに初期化 */
}

/*-----------------------------------------------------------------------------
 *  デストラクタ
 *  XXX: 初期化の仕方によって、デストラクトの方法を変更する必要有
 *-----------------------------------------------------------------------------*/
Agent :: ~Agent() {
  SAFE_DELETE( immune_system_ );
}

/*-----------------------------------------------------------------------------
 *  rebirth()
 *      エージェントを初期化して再利用する
 *-----------------------------------------------------------------------------*/
void Agent :: rebirth() {
  SAFE_DELETE( immune_system_ );
  initGene();
  immune_system_ = new ImmuneSystem;
}
/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
/*-----------------------------------------------------------------------------
 *  エージェントの位置
 *-----------------------------------------------------------------------------*/
void Agent :: setX( int x ) { x_ = x; }                              /* エージェントの位置を設定 */
void Agent :: setY( int y ) { y_ = y; }                              /* エージェントの位置を設定 */
int Agent :: getX() const { return x_; }                             /* エージェントの位置を返す */
int Agent :: getY() const { return y_; }                             /* エージェントの位置を返す */
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( Gene & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool Agent :: infection( Virus &v )
{ return immune_system_->infection( *this, v ); }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: response( Gene & )
 * Description:  先頭のウイルスに対する免疫を獲得するまで、
 *               １期間に１つタグをフリップさせていく。
 *--------------------------------------------------------------------------------------
 */
int Agent :: response()
{ return immune_system_->response( *this ); } 
/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( Virus & )
 * Description:  免疫を獲得しているかどうか
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( Virus &v )                                /* true -> 免疫獲得済み  */
{
  if( getGene().pointOfMinHamDistance( v.getGene() ) < 0 )
    return true;                                                     /* 免疫獲得済み */
  else                                                               /* 0 以上なら */
    return false;                                                    /* 未獲得 */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasVirus( Virus & )
 * Description:  特定のウイルスを保持しているかどうか
 *               リストを走査することで確かめる
 *----------------------------------------------------------------------------------- */
bool Agent :: hasVirus( Virus &v ) const {
    return immune_system_->hasVirus( v );
}
bool Agent :: hasVirus() const {
    return immune_system_->hasVirus();
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: numHoldingVirus()
 * Description:  保持しているウイルスの数
 *--------------------------------------------------------------------------------------
 */
int Agent :: numHoldingVirus() const {
  return immune_system_->getVirusListSize();                         /* ウイルスリストのサイズを返す */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: move
 * Description:  指定された戦略を使用して移動する
 *--------------------------------------------------------------------------------------
 */
void Agent :: move() {
  // if( ! isSymptomaticPeriod() ) { // 症候性期間でなければ
      moving_strategy_->move( x_, y_ );                              /* 戦略を使用して移動する */
  // }
}
__MovingStrategy* Agent :: getMovingStrategy() const { return moving_strategy_; }
