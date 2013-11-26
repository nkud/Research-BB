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
 *      Method:  Landscape :: registAgent( int, int, int )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Landscape :: registAgent( int x, int y, Agent &a ) {
    agent_map_[ x ][ y ].push_back( &a );
}
void Landscape :: removeAgent( const int x, const int y, Agent &a ) {
    ITERATOR(Agent *) it_a = getLandscapeIteratorBeginAt( x, y );
    while( it_a != getLandscapeIteratorEndAt( x, y ) ) {
        if( *it_a == &a ) {
            agent_map_[x][y].erase( it_a );
            return;
        }
        it_a++;
    }
    assert( ! ">>> the agent is not here !" );
    return;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Landscape :: *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
ITERATOR(Agent *) Landscape :: getLandscapeIteratorBeginAt(int x, int y) { return agent_map_[x][y].begin(); }
ITERATOR(Agent *) Landscape :: getLandscapeIteratorEndAt(int x, int y) { return agent_map_[x][y].end(); }
