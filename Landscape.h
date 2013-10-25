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
        void putBackOnMap( int &, int & );
        bool isOnMap( int , int );
};
