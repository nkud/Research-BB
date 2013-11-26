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

class Agent;

class Landscape {
    private:
        VECTOR(Agent *) agent_map_[WIDTH][WIDTH]; /* エージェントの番号を登録する配列 */

    public:
        Landscape();

        void putBackOnMap( int &, int & );      /* マップ上に配置しなおす */
        bool isOnMap( int , int ) const;        /* マップの上にあるか */
        void clearAgentMap();                   /* マップを初期化 */
        void registAgent( int x, int y, Agent & );    /* エージェントを登録 */
        void removeAgent( int x, int y, Agent & ); /* エージェントを削除 */
        ITERATOR(Agent *) getLandscapeIteratorBeginAt( int, int );
        ITERATOR(Agent *) getLandscapeIteratorEndAt( int, int );
};
