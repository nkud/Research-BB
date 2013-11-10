/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sys/time.h>
using namespace std;

#include "Global.h"
#include "Function.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"
#include "Monitor.h"
#include "Administrator.h"

double gettime() {                                                             /* ベンチマーク */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

const int TERM  = 30;                                                          /* 期間  */

int main()
{
    double start, end;                                                         /* タイマー */
    start = gettime();                                                         /* 実行時間計測開始 */

    srand( (unsigned int)time(NULL)/2 );                                       /* 乱数初期化  */

    // 初期化
    Agent agent[ NUM_A ];                                                      /* エージェントの集合  */
    Virus virus[ NUM_V ] = {                                                   /* ウイルス生成 */
        *( new Virus(15, 0.90 )),                                              /* タグ長、感染確率 */
        *( new Virus(20, 0.60 )),                                              /* タグ長、感染確率 */
        *( new Virus(35, 0.15 ))
    };
    Landscape *landscape = new Landscape;                                      /* ランドスケープ初期化 */

    // 管理者に登録
    Administrator AD( agent, virus, landscape );

    Monitor &monitor = Monitor::Instance();                                    /* モニター */

    // 初期感染
    AD.initInfectAgentInRatio( virus[0], 0.1 );                                /* 感染させる */
    AD.initInfectAgentInRatio( virus[1], 0.1 );
    AD.initInfectAgentInRatio( virus[2], 0.1 );
    int initial_num_a = AD.numHasVirus( virus[0] );                            /* 記録しておく */
    int initial_num_b = AD.numHasVirus( virus[1] );

    /* 計測開始 */
    FOR( i, TERM )                                                             /* 計算開始  */
    {
        log("------------ start");

        monitor.resetAll();                                                    /* カウンターをリセット */

        AD.relocateAgent();                                                    /* ランダムに再配置 */
        AD.contactAgent();                                                     /* 近隣に接触する */
        AD.infectAgent();                                                      /* 待機ウイルスを感染させる */
        AD.responseAgent();                                                    /* 免疫応答（タグフリップ） */

        /* 出力 */
        AD.outputFile_HasVirus( "A_hasVirus.txt" );                            /* 出力: ウイルスの保持状況 */
        AD.outputFile_HasImmunity( "A_hasImmunity.txt" );
        AD.outputFile_InfectionContactRatio( "A_infectionContact.txt" );

        log(monitor.num_contact_);
    }

    monitor.generatePlotScript();                                              /* XXX: gnuplot用 */
    
    // 確認用 -----------------------------------------------------------------
    cout << "WIDTH:" << WIDTH << endl;                                         /* => AD.info() */
    cout << "NUM_A:" << NUM_A << endl;
    cout << "NUM_V:" << NUM_V << endl;
    cout << "TAG_LEN_A:" << TAG_LEN_A << endl;
    cout << "VIRUS:" << endl;
    FOR(i,NUM_V) { cout<<"\trate_"<<i<<":\t"<<virus[i].getRate();
        cout<<"\tlen_"<<i<<":\t"<<virus[i].getLen()<<endl; }
    cout << "INIT_NUM_0: " << initial_num_a << endl;
    cout << "INIT_NUM_1: " << initial_num_b << endl;
    FOR( i, NUM_V ) virus[ i ].printTag();                                     /* 全ウイルスのタグを表示 */

    // エージェントの最終的な状態など -----------------------------------------
    ofstream ofs_log("A_log.txt");                                             /* 出力ファイル  */
    ofs_log << "WIDTH:" << WIDTH << endl;
    ofs_log << "NUM_A:" << NUM_A << endl;
    ofs_log << "NUM_V:" << NUM_V << endl;
    ofs_log << "TAG_LEN_A:" << TAG_LEN_A << endl;
    ofs_log << "TAG_LEN_V:" << TAG_LEN_V << endl;
    FOR(i,NUM_V) { ofs_log<<"["<<virus[i].getLen()<<"]:";
        FOR(j, virus[i].getLen()) { ofs_log<<int(virus[i].tagAt(j)); } ofs_log<<endl; }
    ofs_log << ">>> Agent Last Status" << endl;
    FOR(i, NUM_A) { FOR(j, agent[0].getLen()) ofs_log<<agent[i].tagAt(j);
        ofs_log<<" "<<agent[i].numHoldingVirus(); ofs_log<<endl; }
    // ------------------------------------------------------------------------

    // 計測時間出力                             /* XXX: ??? */
    end = gettime();                                                           /* 実行時間計測終了 */
    cout << end-start << endl;
    log(sizeof(Agent));
    log(sizeof(Virus));
    return 0;
}
