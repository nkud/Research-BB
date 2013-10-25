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

#include <vector>

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
 *      Method:  Administrator :: responseAgent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: responseAgent() {
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
//     if( WIDTH*WIDTH < NUM_A-1 ) return;           /* 土地に人数が入らない！ */

    int tx, ty;                                 /* 移動させる場所 */
    FOR( i, NUM_A ) {
        tx = rand_interval_int( 0, WIDTH-1 );   /* ランダムに設定 */
        ty = rand_interval_int( 0, WIDTH-1 );
        agent_[ i ].x_ = tx;                    /* 配置 */
        agent_[ i ].y_ = ty;
        landscape_->agent_map_[ tx ][ ty ].push_back( i );
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

    std::vector<int>::iterator it_infected = infected_agent.begin();
    int tx, ty;                                 /* 感染させるエージェントの位置 */
    VirusData tvdata;                           /* 感染させるウイルス */
    Agent *myself;                              /* 感染者 */

    while( it_infected != infected_agent.end() ) {      /* 感染者リストの数だけ繰り返す */
        myself = &agent_[ *it_infected ];       /* 感染者自身 */
        tx = myself->x_;                        /* 感染者自身の位置 */
        ty = myself->y_;

        REP( i, -1, 1 ) {                       /* 自分の周囲１マスに感染させる（計９マス） */
            REP( j, -1, 1 ) {
                if( !(landscape_->isOnMap( tx+i, ty+j )) ) continue; /* 土地からはみ出てたらスキップ */

                tvdata =                        /* ランダムに保持ウイルスから選んで */
                    myself->vlist_.at( rand_array(myself->vlist_.size()) );

                std::vector<int>::iterator it = landscape_->agent_map_[ tx+i ][ ty+j ].begin();
                while( it != landscape_->agent_map_[ tx+i ][ ty+j ].end() ) { /* その位置にいる人全員に */
                    agent_[ *it ].infection( *tvdata.v_ ); /* ウイルスに感染させる */
                    it++;                       /* その位置にいるの人 */
                }
//                agent_[ landscape_->map_[tx+i][ty+j] ].infection( *tvdata.v_ ); /* ウイルスを感染させる */
            }
        }
        it_infected++;                          /* 次の感染者 */
    }
}
