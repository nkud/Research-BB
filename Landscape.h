/*
 * =====================================================================================
 *
 *       Filename:  Landscape.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"

class Landscape {
    public:
        Landscape();
        int map_[WIDTH][WIDTH];
        bool isOnMap( int, int );
};
