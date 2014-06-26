/*
 * =====================================================================================
 *
 *       Filename:  AgentManager.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU
 *
 * =====================================================================================
 */

#include "Agent.h"
#include "AgentManager.h"
#include "AgentCounter.h"
#include "Landscape.h"
#include "Function.h"

int AgentManager :: numIsIncubation() const {
  int ret = 0;
  EACH( it_a, agents_ ) {
    if( (*it_a)->isIncubationPeriod() ) { ret++; }
  } return ret;
}
int AgentManager :: numIsCrisis() const {
  int ret = 0;
  EACH( it_a, agents_ ) {
    if( (*it_a)->isSymptomaticPeriod() ) { ret++; }
  } return ret;
}

/*-----------------------------------------------------------------------------
 *  AgentManager
 *-----------------------------------------------------------------------------*/
AgentManager :: AgentManager( VECTOR( Agent * ) &agents ) :
  agents_( agents )
{
  LOG("init AgentManager");
}

/*-----------------------------------------------------------------------------
 *  initAgent
 *-----------------------------------------------------------------------------*/

void AgentManager :: initAgent( __MovingStrategy *ms, int len, int num )
{
  FOR( i, num ) {                                                    /* num のだけ */
    agents_.push_back( new Agent( ms, len ) );                  /* 新しくエージェントを加える */
  }
  // マップに配置する
  Landscape::Instance().clearAgentMap();                             /* エージェントの位置をリセット */
  int tx, ty;                                                        /* 移動させる場所 */

  EACH( it_a, getAgentList() )
  {
    tx = rand_interval_int( 0, WIDTH-1 );                            /* ランダムに設定 */
    ty = rand_interval_int( 0, WIDTH-1 );
    (*it_a)->setX( tx );                                             /* 配置 */
    (*it_a)->setY( ty );

    assert( 0 <= tx && tx <= WIDTH-1 );                              /* 土地の外ならエラー */
    assert( 0 <= ty && ty <= WIDTH-1 );

    Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* エージェントを登録 */
  }
}
/*-----------------------------------------------------------------------------
 *  initInfectAgentInRatio( Virus &, double )
 *-----------------------------------------------------------------------------*/
void AgentManager :: initInfectAgentInRatio( Virus &v, double r ) {
  static int infected_from = 0;                                      /* ０番目のエージェントから順に感染させる */
  int infected_to;
  infected_to = infected_from + (int)( getAgentSize() * (r/100) );
  REP( i, infected_from, infected_to ) {
    agents_[ i%getAgentSize() ]->infection( v );
  }
  infected_from = ( infected_to + 1 ) % getAgentSize();              /* 次の感染は、感染した次のエージェントから始まる */
}

/*-----------------------------------------------------------------------------
 *  deleteAgent
 *-----------------------------------------------------------------------------*/
ITERATOR(Agent *) AgentManager :: deleteAgent( ITERATOR(Agent *) &it )
{
  assert( (*it) != NULL );                                           /* メモリが無ければエラー */

  Landscape::Instance().removeAgent( (*it)->getX(), (*it)->getY(), **it );     /* 土地から削除 */

//  delete( *it );                                                     /* メモリ領域を削除 */
  SAFE_DELETE( *it );
  ITERATOR(Agent *) next = agents_.erase( it );                      /* 配列から削除 */

  return next;
}

void AgentManager :: printInitInfo() const {
  std::cout << "\nNUM_A:\t\t" << getAgentSize() << std::endl;
  std::cout << "TAG_LEN_A:\t" << A_DEFAULT_LEN << std::endl;
}
/*-----------------------------------------------------------------------------
 *  numHasVirus
 *-----------------------------------------------------------------------------*/
int AgentManager :: numHasVirus() {
  int ret = 0;
  C_ITERATOR(Agent *) it_a = getAgentIteratorBegin();
  while( it_a != getAgentIteratorEnd() ) {                           /* エージェント全員に対して */
    if( (*it_a)->hasVirus() ) {                                      /* 感染していれば */
      ret++;                                                         /* インクリメント */
    }
    it_a++;
  }
  return ret;                                                        /* v の感染者数を返す */
}
