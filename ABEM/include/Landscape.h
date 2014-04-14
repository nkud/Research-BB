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

#ifndef ___LANDSCAPE
#define ___LANDSCAPE
                                                
#include "Global.h"

#include <vector>

class Agent;


/*
 * =====================================================================================
 *        Class:  Landscape
 *  Description:  エージェントを配置する土地
 * =====================================================================================
 */
class Landscape {
    public:

        /*-----------------------------------------------------------------------------
         *  コンストラクタ
         *-----------------------------------------------------------------------------*/
        Landscape();                                                 /* コンストラクタ */

        /*-----------------------------------------------------------------------------
         *  関数
         *-----------------------------------------------------------------------------*/
        void putBackOnMap( int &, int & );                           /* マップ上に配置しなおす */
        void putAgentOnMap( Agent &a );                              /* エージェントをマップ上に配置しなおす */
        bool isOnMap( int , int ) const;                             /* マップの上にあるか */
        void clearAgentMap();                                        /* マップを初期化 */
        void registAgent( const int x, const int y, Agent & );       /* エージェントを登録 */
        void removeAgent( int x, int y, Agent & );                   /* エージェントを削除 */
        ITERATOR(Agent *) getAgentIteratorBeginAt( int, int );       /* 指定の場所にいるエージェントの配列の先頭 */
        ITERATOR(Agent *) getAgentIteratorEndAt( int, int );         /* 指定の場所にいるエージェントの配列の末尾 */

    private:
        VECTOR(Agent *) agent_map_[WIDTH][WIDTH];                    /* エージェントの番号を登録する配列 */
};

#endif
