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
        while( landscape_->map_[ tx ][ ty ] >= 0 ) { /* もし他の誰かがいたら */
            tx += rand_sign() * 1;              /* となりを見てみる */
            ty += rand_sign() * 1;
            putBackOnMap( tx, ty );             /* 土地の外なら戻す */
        }
        agent_[ i ].x_ = tx;                    /* 配置 */
        agent_[ i ].y_ = ty;
        landscape_->map_[ tx ][ ty ] = i;       /* エージェントのナンバーを記録 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: contactAgent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: contactAgent() {

    std::vector<int> infected_agent;            /* 現時点での感染者リスト */
    FOR( i, NUM_A ) {
        if( agent_[ i ].numHoldingVirus() > 0 ) {/* 何らかのウイルスを保持していたら */
            infected_agent.push_back( i );      /* 感染者リストに加える */
        }
    }

    std::vector<int>::Iterator itv = infected_agent.begin();
    int tx, ty;                                 /* 感染させるエージェントの位置 */
    VirusData *tvdata;                          /* 感染させるウイルス */
    Agent *myself;                              /* 感染者 */

    while( itv != infected_agent.end() ) {      /* 感染者リストの数だけ繰り返す */
        myself = &agent_[ *itv ];               /* 感染者 */
        tx = myself->x_;                        /* 感染者自身の位置 */
        ty = myself->y_;

        REP( i, -1, 1 ) {                       /* 自分の縦横１マスに感染させる（計４マス） */
            REP( j, -1, 1 ) {
                if( i*j != 0 ) continue;        /* 斜めはカウントしないのでスキップ */
                if( !(landscape_->isOnMap( tx+i, ty+j )) ) continue; /* 土地からはみ出てたらスキップ */

                tvdata =                        /* ランダムに保持ウイルスから選んで */
                    myself->vlist_->at( rand_array(myself->vlist_->size()) - 1 );

                agent_[ tx+i ][ ty+j ].infection( tvdata->v_ ); /* ウイルスを感染させる */
            }
        }
        itv++;                                  /* 次の感染者 */
    }
}
