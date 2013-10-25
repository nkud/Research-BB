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
    landscape_( )
{
    FOR( i, WIDTH ) {
        FOR( j, WIDTH ) {
            landscape_[ i ][ j ] = 0;
        }
    }
}
