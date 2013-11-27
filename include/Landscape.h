/*
 * =====================================================================================
 *
 *       Filename:  Landscape.h
 *
 *    Description:  土地
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
        VECTOR(Agent *) agent_map_[WIDTH][WIDTH];                    /* エージェントの番号を登録する配列 */

    public:
        Landscape();                                                 /* コンストラクタ */

        void putBackOnMap( int &, int & );                           /* マップ上に配置しなおす */
        bool isOnMap( int , int ) const;                             /* マップの上にあるか */
        void clearAgentMap();                                        /* マップを初期化 */
        void registAgent( int x, int y, Agent & );                   /* エージェントを登録 */
        void removeAgent( int x, int y, Agent & );                   /* エージェントを削除 */
        ITERATOR(Agent *) getLandscapeIteratorBeginAt( int, int );   /* 指定の場所にいるエージェントの配列の先頭 */
        ITERATOR(Agent *) getLandscapeIteratorEndAt( int, int );     /* 指定の場所にいるエージェントの配列の末尾 */
};
