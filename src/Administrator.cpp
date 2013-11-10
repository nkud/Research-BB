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
        if( agent_[i].hasVirus( v ) ) {                                        /* v に感染していれば */
            ret++;                                                             /* インクリメント */
        }
    }
    return ret;                                                                /* v の感染者数を返す */
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
    landscape_->clearAgentMap();                                               /* エージェントの位置をリセット */
    int tx, ty;                                                                /* 移動させる場所 */
    FOR( i, NUM_A ) {
        tx = rand_interval_int( 0, WIDTH-1 );                                  /* ランダムに設定 */
        ty = rand_interval_int( 0, WIDTH-1 );
        agent_[ i ].setX( tx );                                                /* 配置 */
        agent_[ i ].setY( ty );
        landscape_->agent_map_[ tx ][ ty ].push_back( i );                     /* エージェントを登録 */
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

    std::vector<int> infected_agent;                                           /* 現時点での感染者リスト */
    FOR( i, NUM_A ) {                                                          /* 全員に対して */
        if( agent_[ i ].numHoldingVirus() > 0 ) {                              /* 何らかのウイルスを保持していたら */
            infected_agent.push_back( i );                                     /* 感染者リストに加える */
        }
    }

    int tx, ty;
    Agent *myself;

    ITERATOR(int) it_infected = infected_agent.begin();
    while( it_infected != infected_agent.end() ) {                             /* 感染者リストの数だけ繰り返す */
        myself = &agent_[ *it_infected ];                                      /* 感染者自身 */
        tx = myself->getX();                                                   /* 感染者自身の位置 */
        ty = myself->getY();

        REP( i, -1, 1 ) {                                                      /* 自分の縦・横・自マスに感染させる（計５マス） */
            REP( j, -1, 1 ) {
                if( i*j != 0 ) continue;                                       /* 斜めは入れない */
                if( ! (landscape_->isOnMap( tx+i, ty+j )) ) continue;          /* 土地からはみ出てたらスキップ */

                ITERATOR(int) it = landscape_->agent_map_[ tx+i ][ ty+j ].begin();
                while( it != landscape_->agent_map_[ tx+i ][ ty+j ].end() )
                {                                                              /* その位置にいる人全員に */
                    VirusData *tvdata =                                        /* ランダムに保持ウイルスから選んで */
                        myself->getVirusDataAt( rand_array(myself->getVirusListSize()) );

                    if( static_cast<Virus *>(tvdata->v_)->getRate() > rand_interval_double(0,1) )
                    {                                                          /* ウイルス特有の感染確率で */
                                                                     /* XXX: static castは使いたくない... */
                        agent_[ *it ].pushStandByVirus( tvdata->v_ ); /* 待機ウイルスにする */
                    }
                    it++;                                                      /* 着目をその位置の次にいる人 */

                    Monitor::Instance().countUpContact();                      /* モニタリング */
                }
            }
        }
        it_infected++;                                                         /* 次の感染者 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: infectAgent()
 * Description:  待機ウイルスを感染させる
 *               待機ウイルスの中からランダムに一個選び、感染する
 *--------------------------------------------------------------------------------------
 */
void Administrator :: infectAgent() {
    std::vector<__TagInterface *>::iterator itt;
    __TagInterface *tv;
    int n;

    FOR( i, NUM_A )                                                            /* エージェントの数だけ */
    {
        if( agent_[i].hasNoStandByVirus() ) continue;                      /* 待機ウイルスが無ければスキップ */
        else
        {                                                                      /* あれば */
            while( ! agent_[i].hasNoStandByVirus() ) {                     /* 待機ウイルスがなくなるまで */
                n = rand_array(agent_[i].getStandByListSize() );             /* ランダムに一個の */
                tv = agent_[i].getStandByVirusAt( n );                        /* ウイルスを選んで */
                if( agent_[i].infection( *tv ) ) {                             /* 感染させたら */
                    break;                                                     /* 次のエージェントへ */
                } else {
                    itt = agent_[i].getStandByListBeginIterator();                   /* もし感染しなければ */
                    while(n-->0) { itt++; }                                    /* そのウイルスを */
                    agent_[i].eraseStandByVirus( itt );                    /* 待機ウイルスからはずして次のウイルス */
                }
            }
            agent_[ i ].clearStandByVirus();                               /* 待機ウイルスをクリア */
        }
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
 *      Method:  Administrator :: numHasAllImmunity()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllImmunity() {
    int ret = 0;
    int flag = 1;
    FOR( i, NUM_A ) {
        FOR( j, NUM_V ) {
            if( ! agent_[ i ].hasImmunity( virus_[ j ] ) ) {                   /* もし免疫を持っていなければ、 */
                flag = 0;                                                      /* フラッグを下ろす */
                break;
            }
        }
        if( flag == 1 ) ret++;
        flag = 1;                                                              /* フラッグを戻す */
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
    static int infected_from = 0;                                              /* ０番目のエージェントから順に感染させる */
    int infected_to;
    infected_to = infected_from + (int)( NUM_A * r );
    REP( i, infected_from, infected_to ) {
        agent_[ i%NUM_A ].infection( v );
    }
    infected_from = ( infected_to + 1 ) % NUM_A;                               /* 次の感染は、感染した次のエージェントから始まる */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasVirus( const char *fname ) {
    static std::ofstream ofs(fname);                                           /* インスタンスは１つだけ */
    static int i = 0;                                                          /* 期間をカウント */
    ofs << i++ << SEPARATOR;                                                   /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << numHasVirus( virus_[j] ) << SEPARATOR;                          /* ウイルス j の保持者 */
    }
    ofs << numHasAllVirus() << std::endl;                                      /* 全ウイルス保持者 */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasImmunity
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasImmunity( const char *fname ) {
    static std::ofstream ofs(fname);                                           /* インスタンスは１つだけ */
    static int i = 0;                                                          /* 期間をカウント */
    ofs << i++ << SEPARATOR;                                                   /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << numHasImmunity( virus_[j] ) << SEPARATOR;
    }
    ofs << numHasAllImmunity() << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_InfectionContactRatio( const char *fname ) {
    static std::ofstream ofs(fname);                                           /* インスタンスは１つだけ */
    static int i = 0;                                                          /* 期間をカウント */
    double ratio = 0;
    int sum = 0;

    ofs << i++ << SEPARATOR;                                                   /* 期間 */
    ofs << monitor_.num_contact_ << SEPARATOR;                                 /* 総接触数 */
    FOR( j, NUM_V ) {                                                          /* その内感染した回数 */
        ofs << (sum += monitor_.num_infection_contact_[&virus_[j]]) << SEPARATOR;
    }

    if( sum > 0 ) ratio = (double)sum / (double)monitor_.num_contact_; 
    ofs << ratio << std::endl;
}
