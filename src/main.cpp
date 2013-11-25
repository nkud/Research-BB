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
#include <ctime>
using namespace std;

#include "Global.h"
#include "Function.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"
#include "Monitor.h"
#include "Administrator.h"

int main()
{
#ifdef __unix__
    Benchmark::Instance().startTimer();                    /* ベンチマーク計測開始 */
#endif
    srand( (unsigned int)time(NULL)/2 );                   /* 乱数初期化  */

    // 初期化
    VECTOR(Agent *) agent;                                   /* エージェントの集合  */
    FOR( i, INIT_NUM_A ) {                                  /* 初期エージェントの数だけ */
        agent.push_back( new Agent );                   /* エージェントを初期化 */
    }
    Virus virus[ NUM_V ];                                  /* ウイルス生成 */
    Landscape landscape;                                   /* ランドスケープ初期化 */

    Administrator admin( agent, virus, &landscape );       /* 管理者に登録 */

    Monitor &monitor = Monitor::Instance();                /* モニター */

    // 初期感染
    FOR( i, NUM_V ) {
        admin.initInfectAgentInRatio( virus[i], INIT_INFECTED_RATIO );            /* 初期感染させる */
    }

    admin.relocateAgent();                                 /* ランダムに配置 */

    monitor.generatePlotScript();                          /* XXX: gnuplot用 */

    int zero_count = 0;

    /* 計測開始 */
    FOR( i, TERM )                                         /* 計算開始  */
    {
        log("------------ start");
        cout << "[agent num]: " << admin.getNumOfAgent() << endl;
        admin.incrementTerm();                             /* 期間を進める */

        monitor.resetAll();                                /* モニターのカウンターをリセット */

        admin.moveAgent();                                 /* 移動する */
        admin.contactAgent();                              /* 近隣に接触する */
        admin.infectAgent();                               /* 待機ウイルスを感染させる */
        admin.responseAgent();                             /* 免疫応答（タグフリップ） */

//        admin.agingAgent();
//        admin.matingAgant();

        admin.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ;        /* 出力: ウイルスの保持状況 */
        admin.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ;
        admin.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ;

        /* 途中経過 */
        log( monitor.getContactNum() );
        if( monitor.getContactNum()==0 ) zero_count++;     /* １０回以上接触感染がなければ */
        if( zero_count >= 10 ) break;                      /* 強制的に終了する */
    }
    
    // 確認用 -----------------------------------------------------------------
    admin.printInitInfo();                                 /* 初期状態を表示 */

    // エージェントの最終的な状態など -----------------------------------------
    admin.outputFile_LastLog( "A_log.txt" );

    // ------------------------------------------------------------------------
    // メモ
    // 計測時間出力                             /* XXX: ??? */
#ifdef __unix__
    Benchmark::Instance().stopTimer();                     /* ベンチマークの計測終了 */
    Benchmark::Instance().printTime();                     /* 計測時間表示 */
#endif
    log(sizeof(Agent));
    log(sizeof(Virus));
    log(sizeof(admin));
//    childbirth( *agent[0], *agent[1], *agent[2] );
//    agent[0]->printTag();
//    agent[1]->printTag();
//    agent[2]->printTag();
//    log(agent[0]->getAge());
    return 0;
}
