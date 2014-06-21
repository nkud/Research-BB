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
    assert( (**it_v).isInfectiousPeriod() ); /* 感染性ウイルスでなければエラー */
    if( probability((*it_v)->getRate()) ) {                          /* 感染率に従って */
      getImmuneSystem().pushStandByVirus( *it_v );                  /* 待機ウイルスにする */
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
    __ChildBirthStrategy *cbs,                                       /* 子孫戦略 */
    int len                                                          /* タグ長 */
    ) :
  x_( 0 ),
  y_( 0 ),
  age_( 0 ),
  sex_( __MALE__ ),
  life_( __ALIVE__ ),
  gene_( NULL ),
  immune_system_( NULL ),
  moving_strategy_( ms ),
  childbirth_strategy_( cbs )
{
  immune_system_ = new ImmuneSystem;                                 /* 免疫機構実装 */

  gene_ = new Gene(len);
  gene_->setTagRandom();                                             /* タグをランダムに初期化 */

  sex_ = random_select( __MALE__, __FEMALE__ );                      /* 性別をランダムに初期化 */
  age_ = rand_interval_int( 0, A_MAX_AGE );                          /* 寿命をランダムに設定 */
}

/*-----------------------------------------------------------------------------
 *  移動戦略・子孫戦略・タグ　指定
 *-----------------------------------------------------------------------------*/
Agent :: Agent(
    __MovingStrategy *ms,                                            /* 移動戦略 */
    __ChildBirthStrategy *cbs,                                       /* 子孫戦略 */
    Gene *gene                                                       /* 電子タグ */
    ) :
  x_( 0 ),
  y_( 0 ),
  age_( 0 ),
  sex_( __MALE__ ),
  life_( __ALIVE__ ),
  moving_strategy_( ms ),
  childbirth_strategy_( cbs )
{
  immune_system_ = new ImmuneSystem;                                 /* 免疫機構実装 */

  gene_ = gene;                                                      /* 指定のタグに設定 */
  gene_->setTagRandom();

  sex_ = random_select( __MALE__, __FEMALE__ );                      /* 性別をランダムに初期化 */
  age_ = rand_interval_int( 0, A_MAX_AGE );                          /* 寿命をランダムに設定 */
}
/*-----------------------------------------------------------------------------
 *  移動戦略・子孫戦略・タグ長（最小値~最大値）　指定
 *-----------------------------------------------------------------------------*/
Agent :: Agent( __MovingStrategy *ms, __ChildBirthStrategy *cbs, int minl, int maxl ) :
  x_( 0 ),
  y_( 0 ),
  age_( 0 ),
  sex_( __MALE__ ),
  life_( __ALIVE__ ),
  moving_strategy_( ms ),
  childbirth_strategy_( cbs )
{
  immune_system_ = new ImmuneSystem();                               /* 免疫機構実装 */

  gene_ = new Gene( rand_interval_int(minl, maxl) );                 /* ランダム長にタグを設定 */
  gene_->setTagRandom();                                             /* タグをランダムに初期化 */

  sex_ = random_select( __MALE__, __FEMALE__ );                      /* 性別をランダムに初期化 */
  age_ = rand_interval_int( 0, A_MAX_AGE );                          /* 寿命をランダムに設定 */

}

/*-----------------------------------------------------------------------------
 *  デストラクタ
 *  XXX: 初期化の仕方によって、デストラクトの方法を変更する必要有
 *-----------------------------------------------------------------------------*/
Agent :: ~Agent() {
  assert( gene_ != NULL );
  assert( immune_system_ != NULL );

  SAFE_DELETE( gene_ );
  SAFE_DELETE( immune_system_ );

  gene_ = NULL;
  immune_system_ = NULL;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: resetParam()
 * Description:  エージェントのパラメータをリセット
 *               年齢は０才で初期化
 *--------------------------------------------------------------------------------------
 */
void Agent :: resetParam() {
  age_ = 0;                                                          /* ０才で初期化 */
  if( rand_binary() == 0 ) { sex_ = __MALE__;                        /* 性別をランダムに初期化 */
  } else { sex_ = __FEMALE__; }
  life_ = __ALIVE__;
  // immunesystem reset XXX
}

/*-----------------------------------------------------------------------------
 *  rebirth()
 *      エージェントを初期化して再利用する
 *-----------------------------------------------------------------------------*/
void Agent :: rebirth() {
  resetParam();
  int len = gene_->getLen();

  SAFE_DELETE( gene_ );
  SAFE_DELETE( immune_system_ );

  gene_ = new Gene(len);
  gene_->setTagRandom();
  immune_system_ = new ImmuneSystem;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: birthChild *
 * Description:  出産関連の関数
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasAlreadyGiveBirth() {
  if( give_birth_ ) {                                                /* 出産済みなら */
    return true;                                                     /* true */
  } else {                                                           /* そうでないなら */
    return false;                                                    /* false */
  }
}
void Agent :: setGiveBirth() {
  give_birth_ = true;                                                /* 出産後にする */
}
void Agent :: resetGiveBirth() {
  give_birth_ = false;                                               /* 未出産にする */
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
/*-----------------------------------------------------------------------------
 *  パラメータ
 *-----------------------------------------------------------------------------*/
__LABEL__ Agent :: getSex() const { return sex_; }
int Agent :: getAge() const { return age_; }
bool Agent :: hasAbilityToChildbirth() const
{ if(A_BIRTH_AGE_FROM<=age_ && age_<=A_BIRTH_AGE_TO) return true; else return false; }

void Agent :: setLife( __LABEL__ l ) { life_ = l; }
//bool Agent :: isAlive() const { if( life_ == __ALIVE__ ) return true; else return false; }
//bool Agent :: isDead() const { if( life_ == __DEATH__ ) return false; else return true; }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: aging
 * Description:  老化する
 *--------------------------------------------------------------------------------------
 */
int Agent :: aging() {
  age_++;                                                            /* 年齢をインクリメント */
  return age_;
}

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
bool Agent :: hasImmunity( Virus &v )                    /* true -> 免疫獲得済み  */
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
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: childBirthWith
 * Description:  指定された戦略を使用して移動する
 *--------------------------------------------------------------------------------------
 */
Agent* Agent :: childBirthWith( const Agent &partner ) const {
  return childbirth_strategy_->childbirth( *this, partner );         /* 戦略を使用して移動する */
}
__ChildBirthStrategy* Agent :: getChildBirthStrategy() const { return childbirth_strategy_; }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isOppositeSex( Agent &, Agent & )
 *  Description:  異性であれば true
 * =====================================================================================
 */
bool isOppositeSex( const Agent &a, const Agent &b ) {
  if( a.getSex() == b.getSex() ) {                                   /* 性別が同じなら */
    return false;                                                    /* false */
  } else {                                                           /* 異なれば */
    return true;                                                     /* true */
  }
}
