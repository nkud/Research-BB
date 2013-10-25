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
