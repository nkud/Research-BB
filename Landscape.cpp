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

Landscape :: Landscape() :
    map_( )
{
    FOR( i, WIDTH ) {
        FOR( j, WIDTH ) {
            map_[ i ][ j ] = 0;
        }
    }
}

bool Landscape :: isOnMap( int x, int y) {
    if( x < 0 ) return false;
    if( y < 0 ) return false;
    if( x > WIDTH-1 ) return false;
    if( y > WIDTH-1 ) return false;
    return true;
}
