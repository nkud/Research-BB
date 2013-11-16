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

Landscape :: Landscape()
{
    FOR( i, WIDTH ) FOR( j, WIDTH ) agent_map_[i][j].clear();
    log("init Landscape");
}

void Landscape :: putBackOnMap( int &x, int &y) {
    if( x < 0 ) {
        x = 0;
    }
    if( y < 0 ) {
        y = 0;
    }
    if( x > WIDTH-1 ) {
        x = WIDTH-1;
    }
    if( y > WIDTH-1 ) {
        y = WIDTH-1;
    }
}

bool Landscape :: isOnMap( const int x, const int y) const
{
    if( x < 0 ) {
        return false;
    }
    if( y < 0 ) {
        return false;
    }
    if( x > WIDTH-1 ) {
        return false;
    }
    if( y > WIDTH-1 ) {
        return false;
    }
    return true;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: clearAgentMap()
 * Description:  
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
 *      Method:  Landscape :: pushAgentNumber( int, int, int )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Landscape :: pushAgent( int x, int y, int n ) {
    agent_map_[ x ][ y ].push_back( n );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
ITERATOR(int) Landscape :: getLandscapeIteratorBeginAt(int x, int y) { return agent_map_[x][y].begin(); }
ITERATOR(int) Landscape :: getLandscapeIteratorEndAt(int x, int y) { return agent_map_[x][y].end(); }
