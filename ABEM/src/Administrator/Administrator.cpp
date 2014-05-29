/*
 * =====================================================================================
 *
 *       Filename:  Administrator.cpp
 *
 *    Description:  管理者
 *                  エージェント、ウイルス、土地を管理、統括する
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"
#include "Function.h"
#include "Administrator.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"

#include <vector>
#include <fstream>
#include <iostream>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  コンストラクタ
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( VECTOR(Agent *) &a, VECTOR(Virus *) &v, Landscape *l ) :
  agent_( a ),
  virus_( v ),
  landscape_( l ),
  term_( 0 )
{
  assert( &a != 0 );                                                 /* NULLならエラー */
  assert( &v != 0 );                                                 /* NULLならエラー */
  assert( l != 0 );                                                  /* NULLならエラー */

  model_strategy_ = new __ModelStrategy( this );                     /* デフォルトモデル */

//  agent_.reserve( A_MAX_NUM );                                       /* 最大エージェント数まで領域確保 */
}

Administrator :: Administrator( VECTOR(Agent *) &a, VECTOR(Virus *) &v, Landscape *l,
    __ModelStrategy *model ) :
  agent_( a ),
  virus_( v ),
  landscape_( l ),
  model_strategy_( model ),
  term_( 0 )
{
  assert( &a != 0 );                                                 /* NULLならエラー */
  assert( &v != 0 );                                                 /* NULLならエラー */
  assert( l != 0 );                                                  /* NULLならエラー */
  assert( model != 0 );                                              /* NULLならエラー */

  model_strategy_->setAdministrator( this );

  agent_.reserve( A_MAX_NUM );                                       /* 最大エージェント数まで領域確保 */
}

/*-----------------------------------------------------------------------------
 *  initAgent, initVirus
 *      エージェント・ウイルスを初期化
 *-----------------------------------------------------------------------------*/
void Administrator :: initAgent( __MovingStrategy *mbs, __ChildBirthStrategy *cbs, int len, int num )
{ model_strategy_->initAgent( mbs, cbs, len, num ); }
void Administrator :: initVirus()
{ model_strategy_->initVirus(); }

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: *
 * Description:  getter
 *----------------------------------------------------------------------------------- */
VECTOR(Agent *) *Administrator :: agent() { return &agent_; }
VECTOR(Virus *) *Administrator :: virus() { return &virus_; }
Landscape *Administrator :: landscape() { return landscape_; }
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: deleteAgent()
 * Description:  配列から指定のエージェントを削除
 *--------------------------------------------------------------------------------------
 */
ITERATOR(Agent *) Administrator :: deleteAgent( ITERATOR(Agent *) &it )
{
  assert( (*it) != NULL );                                           /* メモリが無ければエラー */

  landscape_->removeAgent( (*it)->getX(), (*it)->getY(), **it );     /* 土地から削除 */

  delete( *it );                                                     /* メモリ領域を削除 */
  ITERATOR(Agent *) next = agent_.erase( it );                        /* 配列から削除 */

  return next;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: agingAgent()
 * Description:  老化させる
 *               寿命を越えたら、死亡処理をする
 *--------------------------------------------------------------------------------------
 */
void Administrator :: agingAgent()
{
  model_strategy_->aging();
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: matingAgant()
 * Description:  交配し、新たなエージェントを誕生させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: matingAgant() {
  model_strategy_->mating();
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: getNumOfAgent()
 * Description:  現在の総エージェント数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: getNumOfAgent() const {
  return agent_.size();                                              /* 現在の総エージェント数 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasVirus( Tag & )
 * Description:  現在の感染者数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasVirus( Virus &v ) const {
  int ret = 0;
  ITERATOR(Agent *) it_a = agent_.begin();
  while( it_a != agent_.end() ) {                                    /* エージェント全員に対して */
    if( (*it_a)->hasVirus( v ) ) {                                   /* v に感染していれば */
      ret++;                                                         /* インクリメント */
    }
    it_a++;
  }
  return ret;                                                        /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasImmunity( Tag & )
 * Description:  現在の免疫獲得者数数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasImmunity( Virus &v ) const {
  int ret = 0;
  ITERATOR(Agent *) it_a = agent_.begin();
  while( it_a != agent_.end() ) {                                    /* エージェント全員に対して */
    if ( (*it_a)->hasImmunity( v ) ) {                               /* v の免疫を獲得していれば*/
      ret++;                                                         /* インクリメント */
    }
    it_a++;
  }
  return ret;                                                        /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: responseAgent()
 * Description:  エージェント全員に対して免疫応答させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: responseAgent() {
  model_strategy_->response();
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator:: relocateAgent()
 * Description:  エージェントをランダムに再配置
 *               １つのところに複数人数も許可
 *--------------------------------------------------------------------------------------
 */
void Administrator :: relocateAgent() {
  landscape_->clearAgentMap();                                       /* エージェントの位置をリセット */
  int tx, ty;                                                        /* 移動させる場所 */

  ITERATOR(Agent *) it_a = agent_.begin();                           /* エージェントの先頭から */
  while( it_a != agent_.end() ) {                                    /* 末尾まで */
    tx = rand_interval_int( 0, WIDTH-1 );                            /* ランダムに設定 */
    ty = rand_interval_int( 0, WIDTH-1 );
    (*it_a)->setX( tx );                                             /* 配置 */
    (*it_a)->setY( ty );

    assert( 0 <= tx && tx <= WIDTH-1 );                              /* 土地の外ならエラー */
    assert( 0 <= ty && ty <= WIDTH-1 );

    landscape_->registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* エージェントを登録 */
    it_a++;
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: moveAgent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: moveAgent() {
  model_strategy_->migrate();
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: contactAgent()
 * Description:  自分の縦横自マス（計５マス）に対して
 *               自分の保持ウイルスリストからランダムに１つ選び出し全員に感染させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: contactAgent() {
  model_strategy_->contact();
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: infectAgent()
 * Description:  待機ウイルスを感染させる
 *               待機ウイルスの中からランダムに一個選び、感染する
 *--------------------------------------------------------------------------------------
 */
void Administrator :: infectAgent() {
  model_strategy_->infect();
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasAllVirus()
 * Description:  すべてのウイルスに感染している数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllVirus() const {
  int ret = 0;

  ITERATOR(Agent *) it_a = agent_.begin();
  while( it_a != agent_.end() ) {                                    /* エージェント全員に対して */
    if( (*it_a)->numHoldingVirus() == (int)virus_.size() ) {              /* 全ウイルスを保持していれば */
      ret++;                                                         /* 数える*/
    }
    it_a++;
  }
  return ret;
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasAllImmunity()
 * Description:  すべてのウイルスに対して免疫獲得している数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllImmunity() const {
  int ret = 0;
  int flag = 1;

  ITERATOR(Agent *) it_a = agent_.begin();                           /* エージェントの先頭から */
  while( it_a != agent_.end() ) {                                    /* 末尾まで */
    FOR( j, (int)virus_.size() ) {                                        /* すべてのウイルスに関して調べる */
      if( ! (*it_a)->hasImmunity( *virus_[ j ] ) ) {                 /* もし免疫を持っていなければ */
        flag = 0;                                                    /* フラッグを下ろして */
        break;                                                       /* ループを抜ける */
      }
    }
    if( flag == 1 ) ret++;                                           /* すべての免疫を持って入れば数える */
    flag = 1;                                                        /* フラッグを戻す */
    it_a++;                                                          /* 次のエージェントへ */
  }
  return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: initInfectAgentInRatio( Virus &, double )
 * Description:  初期感染させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: initInfectAgentInRatio( Virus &v, double r ) {
  static int infected_from = 0;                                      /* ０番目のエージェントから順に感染させる */
  int infected_to;
  infected_to = infected_from + (int)( agent_.size() * r );
  REP( i, infected_from, infected_to ) {
    agent_[ i%agent_.size() ]->infection( v );
  }
  infected_from = ( infected_to + 1 ) % agent_.size();               /* 次の感染は、感染した次のエージェントから始まる */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: printInitInfo()
 * Description:  初期状態を表示（端末）
 *--------------------------------------------------------------------------------------
 */
void Administrator :: printInitInfo() const {
  std::cout << "WIDTH:" << WIDTH << std::endl;                       /* 幅 */
  std::cout << "\nNUM_A:\t\t" << agent_.size() << std::endl;
  std::cout << "TAG_LEN_A:\t" << A_DEFAULT_LEN << std::endl;
  std::cout << "\nNUM_V:\t\t" << virus_.size() << std::endl;

  std::cout << "VIRUS:" << std::endl;                                /* ウイルス情報 */
  FOR(i, (int)virus_.size()) {
    std::cout<<"\trate_"<<i<<":\t"<<(*virus_[i]).getRate();
    std::cout<<"\tlen_"<<i<<":\t"<<(*virus_[i]).getTag()->getLen()<<std::endl;
  }
  FOR( i, (int)virus_.size() ) {
    (*virus_[ i ]).getTag()->printTag();       /* 全ウイルスのタグを表示 */
  }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: *
 * Description:  期間系の関数
 *--------------------------------------------------------------------------------------
 */
void Administrator :: incrementTerm() {
  term_++;                                                           /* 期間をインクリメント */
}
int Administrator :: getTerm() const {
  return term_;                                                      /* 現在の期間 */
}
