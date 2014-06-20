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

#include "Config.h"
#include "Function.h"

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
//        Landscape();                                                 /* コンストラクタ */
        static Landscape& Instance() {
          static Landscape singleton;
          return singleton;
        }

        /*-----------------------------------------------------------------------------
         *  関数
         *-----------------------------------------------------------------------------*/
        void putBackOnMap( int &, int & );                           /* マップ上に配置しなおす */
        void putAgentOnMap( Agent &a );                              /* エージェントをマップ上に配置しなおす */
        bool isOnMap( int , int ) const;                             /* マップの上にあるか */
        void clearAgentMap();                                        /* マップを初期化 */
        void registAgent( const int x, const int y, Agent & );       /* エージェントを登録 */
        void removeAgent( int x, int y, Agent & );                   /* エージェントを削除 */
        VECTOR(Agent *) & getAgentList( int x, int y ) { return agent_map_[x][y]; }

        VECTOR(Agent *) getNeighbors( const Agent & );



        void setWidth( int w ) {
          assert( getWidth() == 0 and "initialization is one time");
          width_ = w;
        }
        const int getWidth() const { return width_; }
        void initialize( int w ) {
          setWidth(w);
        }

    private:
        VECTOR(Agent *) agent_map_[WIDTH][WIDTH];                    /* エージェントの番号を登録する配列 */
        int width_;
        Landscape();
};

#endif
