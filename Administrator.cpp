/*
 * =====================================================================================
 *
 *       Filename:  Administrator.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"
#include "Function.h"
#include "Administrator.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( Agent *a, Virus *v, Landscape *l ) :
    agent_( a ),
    virus_( v ),
    landscape_( l )
{}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numIsInfected( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numIsInfected( __TagInterface &v ) {
    int ret = 0;

    FOR( i, NUM_A ) {
        if( agent_[i].isInfected( v ) ) {       /* v に感染していれば */
            ret++;                              /* インクリメント */
        }
    }
    return ret;                                 /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasImmunity( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasImmunity( __TagInterface &v ) {
    int ret = 0;

    FOR( i, NUM_A ) {
        if (agent_[i].hasImmunity( v ) ) {
            ret++;
        }
    }
    return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: allResponse()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: allResponse() {
    FOR( i, NUM_A ) {
        agent_[ i ].response();
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator:: relocateAgent()
 * Description:  エージェントをランダムに再配置
 *               １つの位置には１人だけ
 *--------------------------------------------------------------------------------------
 */
void Administrator :: relocateAgent() {
    int tx, ty;                                 /* 移動させる場所 */
    FOR( i, NUM_A ) {
        tx = rand_interval_int( 0, WIDTH-1 );   /* ランダムに設定 */
        ty = rand_interval_int( 0, WIDTH-1 );
        while( landscape_->map_[ tx ][ ty ] > 0 ) { /* もし他の誰かがいたら */
            tx += rand_sign() * 1;                /* となりを見てみる */
            ty += rand_sign() * 1;
        }
        agent_[ i ].x_ = tx;                    /* 配置 */
        agent_[ i ].y_ = ty;
    }
}
