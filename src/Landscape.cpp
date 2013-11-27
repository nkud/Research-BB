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

#include <cassert>
 
Landscape :: Landscape()
{
    FOR( i, WIDTH ) FOR( j, WIDTH ) agent_map_[i][j].clear();        /* エージェントのマップをクリア */
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
    if( x < 0 ) { x = 0; }
    if( y < 0 ) { y = 0; }
    if( x > WIDTH-1 ) { x = WIDTH-1; }
    if( y > WIDTH-1 ) { y = WIDTH-1; }
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
    agent_map_[ x ][ y ].push_back( &a );                            /* エージェントを登録 */
}
void Landscape :: removeAgent( const int x, const int y, Agent &a ) {
    ITERATOR(Agent *) it_a = getLandscapeIteratorBeginAt( x, y );    /* 指定の場所の配列の先頭から */
    while( it_a != getLandscapeIteratorEndAt( x, y ) ) {             /* 末尾まで */
        if( *it_a == &a ) {                                          /* エージェントを探して */
            agent_map_[x][y].erase( it_a );                          /* 削除する */
            return;                                                  /* 終了 */
        }
        it_a++;
    }
    assert( ! ">>> the agent is not here !" );                       /* 見つからなければエラー */
    return;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: *
 * Description:  セッタ / ゲッタ
 *               指定の場所のエージェント配列の先頭・末尾へのイテレータを返す
 *--------------------------------------------------------------------------------------
 */
ITERATOR(Agent *) Landscape :: getLandscapeIteratorBeginAt(int x, int y) { return agent_map_[x][y].begin(); }
ITERATOR(Agent *) Landscape :: getLandscapeIteratorEndAt(int x, int y) { return agent_map_[x][y].end(); }
