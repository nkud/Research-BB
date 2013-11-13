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
    private:
        std::vector<int> agent_map_[WIDTH][WIDTH]; /* エージェントの番号を登録する配列 */

    public:
        Landscape();

        void putBackOnMap( int &, int & );      /* マップ上に配置しなおす */
        bool isOnMap( int , int );              /* マップの上にあるか */
        void clearAgentMap();                   /* マップを初期化 */
        void pushAgent( int, int, int );        /* エージェントを登録 */
        ITERATOR(int) getLandscapeBeginIterator( int, int );
        ITERATOR(int) getLandscapeEndIterator( int, int );
};
