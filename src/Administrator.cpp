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
#include <iostream>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: *
 * Description:  期間系の関数
 *--------------------------------------------------------------------------------------
 */
void Administrator :: incrementTerm() {
    term_++;
}
int Administrator :: getTerm() {
    return term_;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( Agent *a, Virus *v, Landscape *l ) :
    term_( 0 ),
    agent_( a ),
    virus_( v ),
    landscape_( l )
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
        if( agent_[i].hasVirus( v ) ) {                    /* v に感染していれば */
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
        agent_[ i ].setX( tx );                            /* 配置 */
        agent_[ i ].setY( ty );
        landscape_->pushAgent( tx, ty, i );                /* エージェントを登録 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: moveAgent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: moveAgent() {
    landscape_->clearAgentMap();                           /* エージェントの位置をリセット */
    FOR( i, NUM_A ) {
        int tx = rand_interval_int( -MOVE_DISTANCE, MOVE_DISTANCE ); /* 相対的に x を動かす量*/
        int ty = rand_interval_int( -MOVE_DISTANCE, MOVE_DISTANCE ); /* 相対的に y を動かす量 */
        int xx = tx + agent_[i].getX();                    /* x 座標を設定 */
        int yy = ty + agent_[i].getY();                    /* y 座標を設定 */
        if( ! landscape_->isOnMap( xx, yy ) ) {            /* もし移動先が土地の上になっていなければ */
            landscape_->putBackOnMap( xx, yy );            /* 土地の上に戻す */
        }
        agent_[i].setX( xx );                              /* 移動を実行 */
        agent_[i].setY( yy );
        landscape_->pushAgent( xx, yy, i );                /* エージェントを土地に登録 */
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

    int tx, ty;
    Agent *myself;

    FOR( i, NUM_A ) {
        myself = &agent_[ i ];                             /* 感染者自身 */
        if( myself->numHoldingVirus() <= 0 ) continue;     /* 健康ならスキップ */
        tx = myself->getX();                               /* 感染者自身の位置 */
        ty = myself->getY();

        REP( i, -1, 1 ) {                                  /* 自分の縦・横・自マスに感染させる（計５マス） */
            REP( j, -1, 1 ) {
#ifdef NO_DIAGONAL
                if( i*j != 0 ) continue;                   /* 斜めは入れない */
#endif
                if( ! (landscape_->isOnMap( tx+i, ty+j )) ) continue;          /* 土地からはみ出てたらスキップ */

                ITERATOR(int) it = landscape_->getLandscapeIteratorBeginAt( tx+i, ty+j );
                while( it != landscape_->getLandscapeIteratorEndAt( tx+i, ty+j ) )
                {                                          /* その位置にいる人全員に */
                    VirusData *tvdata =                    /* ランダムに保持ウイルスから選んで */
                        myself->getVirusDataAt( rand_array(myself->getVirusListSize()) );

                    if( tvdata->v_->getRate() > rand_interval_double(0,1) )
                    {                                      /* ウイルス特有の感染確率で */
                        agent_[ *it ].pushStandByVirus( tvdata->v_ );          /* 待機ウイルスにする */
                    }
                    it++;                                  /* 着目をその位置の次にいる人 */

                    Monitor::Instance().countUpContact();  /* モニタリング */
                }
            }
        }
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
    ITERATOR(Virus *) itt;
    Virus *tv;
    int n;
    int infection_count;                                   /* 同時感染数をカウント。最大値を越えないように */

    FOR( i, NUM_A )                                        /* エージェントの数だけ */
    {
        if( agent_[i].hasNoStandByVirus() ) continue;      /* 待機ウイルスが無ければスキップ */
        else {                                             /* あれば */
            infection_count = 0;

            while( ! agent_[i].hasNoStandByVirus() ) {     /* 待機ウイルスがなくなるまで */
                if( infection_count >= MAX_V_AGENT_INFECT_ONT_TIME ) { /* もし最大同時感染数を越えそうなら */
                    break;                                 /* 次のエージェントへ */
                }

                n = rand_array( agent_[i].getStandByListSize() );             /* ランダムに一個の */
                tv = agent_[i].getStandByVirusAt( n );     /* ウイルスを選んで */

                if( agent_[i].infection( *tv ) ) {         /* 感染させたら */
                    infection_count++;                     /* カウントを増やす */
//                    break;                                 /* 次のエージェントへ */
                } else {
                    itt = agent_[i].getStandByListIteratorBegin();                   /* もし感染しなければ */
                    while(n-->0) { itt++; }                /* そのウイルスを */
                    agent_[i].eraseStandByVirus( itt );    /* 待機ウイルスからはずして次のウイルス */
                }

            }
            agent_[ i ].clearStandByVirus();               /* 待機ウイルスをクリア */
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
                flag = 0;                                  /* フラッグを下ろす */
                break;
            }
        }
        if( flag == 1 ) ret++;
        flag = 1;                                          /* フラッグを戻す */
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
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                       /* インスタンスは１つだけ */
    ofs << getTerm() << SEPARATOR;                         /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << numHasVirus( virus_[j] ) << SEPARATOR;      /* ウイルス j の保持者 */
    }
    ofs << numHasAllVirus() << std::endl;                  /* 全ウイルス保持者 */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasImmunity
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasImmunity( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                       /* インスタンスは１つだけ */
    ofs << getTerm() << SEPARATOR;                         /* ファイルに出力 */
    FOR( k, NUM_V ) {
        ofs << numHasImmunity( virus_[k] ) << SEPARATOR;   /* ウイルスに対する免疫獲得者数 */
    }
    ofs << numHasAllImmunity() << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_InfectionContactRatio( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                       /* インスタンスは１つだけ */
    double ratio = 0;
    int sum = 0;                                           /* 何らかのウイルスに感染した接触回数 */

    ofs << getTerm() << SEPARATOR;                         /* 期間 */
    ofs << Monitor::Instance().getContactNum() << SEPARATOR; /* 総接触数 */
    FOR( j, NUM_V ) {                                      /* その内感染した回数 */
        sum += Monitor::Instance().getInfectionContactNum(&virus_[j]);
        ofs << Monitor::Instance().getInfectionContactNum(&virus_[j]) << SEPARATOR;
    }

    if( sum > 0 ) ratio = (double)sum / (double) Monitor::Instance().getContactNum(); 
    ofs << ratio << std::endl;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_LastLog( const char * )
 * Description:  最終、初期状態を出力
 *--------------------------------------------------------------------------------------
 */
void Administrator :: outputFile_LastLog( const char *fname ) {
    static std::ofstream ofs(fname);
    ofs << "WIDTH:" << WIDTH << std::endl;
    ofs << "NUM_A:" << NUM_A << std::endl;
    ofs << "NUM_V:" << NUM_V << std::endl;
    ofs << "TAG_LEN_A:" << TAG_LEN_A << std::endl;
    ofs << "TAG_LEN_V:" << TAG_LEN_V << std::endl;
    FOR(i,NUM_V) { ofs<<"["<<virus_[i].getLen()<<"]:";
        FOR(j, virus_[i].getLen()) { ofs<<int(virus_[i].tagAt(j)); } ofs<<std::endl; }
    ofs << ">>> Agent Last Status" << std::endl;
    FOR(i, NUM_A) { FOR(j, agent_[0].getLen()) ofs<<agent_[i].tagAt(j);
        ofs<<" "<<agent_[i].numHoldingVirus(); ofs<<std::endl; }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: printInitInfo()
 * Description:  初期状態を表示（端末）
 *--------------------------------------------------------------------------------------
 */
void Administrator :: printInitInfo() {
    std::cout << "WIDTH:" << WIDTH << std::endl;           /* 幅 */
    std::cout << "\nNUM_A:\t\t" << NUM_A << std::endl;
    std::cout << "TAG_LEN_A:\t" << TAG_LEN_A << std::endl;
    std::cout << "\nNUM_V:\t\t" << NUM_V << std::endl;

    std::cout << "VIRUS:" << std::endl;                    /* ウイルス情報 */
    FOR(i,NUM_V) { std::cout<<"\trate_"<<i<<":\t"<<virus_[i].getRate();
        std::cout<<"\tlen_"<<i<<":\t"<<virus_[i].getLen()<<std::endl; }
    FOR( i, NUM_V ) virus_[ i ].printTag();                /* 全ウイルスのタグを表示 */

//    std::cout << "INIT_NUM_0: " << initial_num_a << std::endl;
//    std::cout << "INIT_NUM_1: " << initial_num_b << std::endl;

}
