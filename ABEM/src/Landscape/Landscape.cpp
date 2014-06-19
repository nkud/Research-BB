/*
 * =====================================================================================
 *
 *       Filename:  Landscape.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Landscape.h"
#include "Agent.h"
#include "Function.h"

#include <cassert>


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: getNeighbors
 * Description:  近隣の配列を取得する
 *--------------------------------------------------------------------------------------
 */
VECTOR(Agent *)
Landscape :: getNeighbors( const Agent &agent )
{
  int x = agent.getX();
  int y = agent.getY();
  VECTOR(Agent *) neighbors;                                         /* 近隣の配列 */
  REP(i, -1, 1) {                                                    /* 周りの土地に対して */
    REP(j, -1, 1) {
      if( isOnMap(x+i, y+j) ) {                                      /* はみ出していなければ */
        EACH( it_a, getAgentList(x+i, y+j) ) {                       /* その場所のエージェントを */
          neighbors.push_back( *it_a );                              /* 近隣に追加する */
        }
      }
    }
  }
  EACH( it_n, neighbors ) {
    if ( *it_n == &agent ) {                                         /* 自分は */
      neighbors.erase(it_n);                                         /* 削除 */
      break;
    }
  }
  return neighbors;
}

Landscape :: Landscape()
{
  clearAgentMap();
  log("init Landscape");
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: putBackOnMap( int &, int & )
 * Description:  土地からはみでたエージェントの位置を土地の上に戻す
 *               壁の役割
 *--------------------------------------------------------------------------------------
 */
void Landscape :: putBackOnMap( int &x, int &y) {
  while( x < 0 ) x += WIDTH;
  while( y < 0 ) y += WIDTH;
  x %= WIDTH;
  y %= WIDTH;
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: putAgentOnMap( Agent & )
 * Description:  土地からはみでたエージェントの位置を土地の上に戻す
 *               壁の役割
 *--------------------------------------------------------------------------------------
 */
void Landscape :: putAgentOnMap( Agent &a ) {
  int x = a.getX();                                                  /* 座標を取得する */
  int y = a.getY();

  putBackOnMap( x, y );                                              /* 土地に配置する */

  assert( isOnMap(x,y) );

  a.setX( x );                                                       /* 座標を設定しなおす */
  a.setY( y );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: isOnMap( const int &, const int & ) const
 * Description:  土地の上にあるかどうか
 *--------------------------------------------------------------------------------------
 */
bool Landscape :: isOnMap( const int x, const int y) const
{
  if( x < 0 ) { return false; }
  if( y < 0 ) { return false; }
  if( x > WIDTH-1 ) { return false; }
  if( y > WIDTH-1 ) { return false; }
  return true;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: clearAgentMap()
 * Description:  マップをクリアする
 *--------------------------------------------------------------------------------------
 */
void Landscape :: clearAgentMap() {
  FOR( i, WIDTH ) {
    FOR( j, WIDTH ) {
      agent_map_[ i ][ j ].clear();
    }
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: registAgent / removeAgent( int, int, Agent & )
 * Description:  土地にエージェントのポインタを登録 / 削除
 *--------------------------------------------------------------------------------------
 */
void Landscape :: registAgent( const int x, const int y, Agent &a ) {
  agent_map_[ x ][ y ].push_back( &a );                              /* エージェントを登録 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: removeAgent
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Landscape :: removeAgent( const int x, const int y, Agent &a ) {
  EACH( it_a, getAgentList(x, y) ) {
    if( *it_a == &a ) {                                              /* エージェントを探して */
      agent_map_[x][y].erase( it_a );                                /* 削除する */
      return;                                                        /* 終了 */
    }
  }
  assert( ! ">>> this agent is not here !" );                        /* 見つからなければエラー */
  return;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: *
 * Description:  セッタ / ゲッタ
 *               指定の場所のエージェント配列の先頭・末尾へのイテレータを返す
 *--------------------------------------------------------------------------------------
 */
ITERATOR(Agent *) Landscape :: getAgentIteratorBeginAt(int x, int y) { return agent_map_[x][y].begin(); }
ITERATOR(Agent *) Landscape :: getAgentIteratorEndAt(int x, int y) { return agent_map_[x][y].end(); }
