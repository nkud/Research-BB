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
#include "Monitor.h"

#include <vector>
#include <fstream>

#define INT_ITERATOR    std::vector<int>::iterator

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( Agent *a, Virus *v, Landscape *l ) :
    agent_( a ),
    virus_( v ),
    landscape_( l ),
    monitor_( Monitor::Instance() )
{}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasVirus( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasVirus( __TagInterface &v ) {
    int ret = 0;

    FOR( i, NUM_A ) {
        if( agent_[i].isInfected( v ) ) {                  /* v に感染していれば */
            ret++;                                         /* インクリメント */
        }
    }
    return ret;                                            /* v の感染者数を返す */
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
 *               １つのところに複数人数も許可
 *--------------------------------------------------------------------------------------
 */
void Administrator :: relocateAgent() {
    landscape_->clearAgentMap();                           /* エージェントの位置をリセット */
    int tx, ty;                                            /* 移動させる場所 */
    FOR( i, NUM_A ) {
        tx = rand_interval_int( 0, WIDTH-1 );              /* ランダムに設定 */
        ty = rand_interval_int( 0, WIDTH-1 );
        agent_[ i ].x_ = tx;                               /* 配置 */
        agent_[ i ].y_ = ty;
        landscape_->agent_map_[ tx ][ ty ].push_back( i ); /* エージェントを登録 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: contactAgent()
 * Description:  自分の縦横自マス（計５マス）に対して
 *               自分の保持ウイルスリストからランダムに１つ選び出し全員に感染させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: contactAgent() {

    std::vector<int> infected_agent;                       /* 現時点での感染者リスト */
    FOR( i, NUM_A ) {                                      /* 全員に対して */
        if( agent_[ i ].numHoldingVirus() > 0 ) {          /* 何らかのウイルスを保持していたら */
            infected_agent.push_back( i );                 /* 感染者リストに加える */
        }
    }

    int tx, ty;
    VirusData tvdata;
    Agent *myself;

    INT_ITERATOR it_infected = infected_agent.begin();
    while( it_infected != infected_agent.end() ) {         /* 感染者リストの数だけ繰り返す */
        myself = &agent_[ *it_infected ];                  /* 感染者自身 */
        tx = myself->x_;                                   /* 感染者自身の位置 */
        ty = myself->y_;

        REP( i, -1, 1 ) {                                  /* 自分の縦・横・自マスに感染させる（計５マス） */
            REP( j, -1, 1 ) {
                if( i*j != 0 ) continue;
                if( !(landscape_->isOnMap( tx+i, ty+j )) ) continue; /* 土地からはみ出てたらスキップ */

                INT_ITERATOR it = landscape_->agent_map_[ tx+i ][ ty+j ].begin();
                while( it != landscape_->agent_map_[ tx+i ][ ty+j ].end() )
                {                                          /* その位置にいる人全員に */
                tvdata =                                   /* ランダムに保持ウイルスから選んで */
                    myself->vlist_.at( rand_array(myself->vlist_.size()) );

                    agent_[ *it ].infection( *tvdata.v_ ); /* ウイルスを感染させる */
                    it++;                                  /* 着目をその位置の次にいる人 */

                    Monitor::Instance().countUpContact();
                }
            }
        }
        it_infected++;                                     /* 次の感染者 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasAllVirus()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllVirus() {
    int ret = 0;
    FOR( i, NUM_A ) {
        if( agent_[ i ].numHoldingVirus() == NUM_V ) ret++;
    }
    return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: initInfectAgentInRatio( Virus &, double )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: initInfectAgentInRatio( Virus &v, double r ) {
    static int infected_from = 0;                          /* ０番目のエージェントから順に感染させる */
    int infected_to;
    infected_to = infected_from + (int)( NUM_A * r );
    int n;
    REP( i, infected_from, infected_to ) {
        agent_[ i%NUM_A ].infection( v );
    }
    infected_from = ( infected_to + 1 ) % NUM_A;           /* 次の感染は、感染した次のエージェントから始まる */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasVirus( const char *fname ) {
    static std::ofstream ofs(fname);                       /* インスタンスは１つだけ */
    static int i = 0;                                      /* 期間をカウント */
    ofs << i++ << SEPARATOR;                               /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << numHasVirus( virus_[j] ) << SEPARATOR;      /* ウイルス i の保持者 */
    }
    ofs << numHasAllVirus() << std::endl;                  /* 全ウイルス保持者 */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_InfectionContactRatio( const char *fname ) {
    static std::ofstream ofs(fname);                       /* インスタンスは１つだけ */
    static int i = 0;                                      /* 期間をカウント */
    double ratio = 0;
    ofs << i++ << SEPARATOR;                               /* ファイルに出力 */
    if( monitor_.num_contact_ == 0 ||
            monitor_.num_infection_contact_ == 0) 
        ratio = 0;
    else
        ratio = (double)monitor_.num_infection_contact_ /
            (double)monitor_.num_contact_;
    ofs << monitor_.num_contact_ << SEPARATOR
        << monitor_.num_infection_contact_ << SEPARATOR
        << ratio << std::endl;      /* ウイルス i の保持者 */
}
