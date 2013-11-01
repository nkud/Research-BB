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
#include <vector>

class Landscape {
    public:
        Landscape();
        int map_[WIDTH][WIDTH];
        void putBackOnMap( int &, int & );
        bool isOnMap( int , int );

        std::vector<int> agent_map_[WIDTH][WIDTH];
        void clearAgentMap();
};
