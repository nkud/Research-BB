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
    Benchmark::Instance().startTimer();                              /* ベンチマーク計測開始 */
#endif
    srand( (unsigned int)time(NULL)/2 );                             /* 乱数初期化  */

    // 初期化
    VECTOR(Agent *) agent;                                           /* エージェントの集合  */
    FOR( i, INIT_NUM_A ) {                                           /* 初期エージェントの数だけ */
        agent.push_back( new Agent );                                /* エージェントを初期化 */
    }
    Virus virus[ NUM_V ];                                            /* ウイルス生成 */
    Landscape landscape;                                             /* ランドスケープ初期化 */

    Administrator admin( agent, virus, &landscape );                 /* 管理者に登録 */

    Monitor &monitor = Monitor::Instance();                          /* モニター */

    // 初期感染
    FOR( i, NUM_V ) {
        admin.initInfectAgentInRatio( virus[i], INIT_INFECTED_RATIO );            /* 初期感染させる */
    }

    admin.relocateAgent();                                           /* ランダムに配置 */

    monitor.generatePlotScript();                                    /* gnuplot用ファイル出力 */
    monitor.generatePlotScriptForPng();                              /* gnuplot用ファイル出力 */
    monitor.generateResultHtml();                                    /* 結果表示用HTMLファイル出力 */

    int zero_count = 0;

    /* 計測開始 */
    FOR( i, TERM )                                                   /* 計算開始  */
    {
        cout << "===================================" << endl;
        LOG( i );
        LOG( admin.getNumOfAgent() );

        admin.incrementTerm();                                       /* 期間を進める */

        monitor.resetAll();                                          /* モニターのカウンターをリセット */

        /* A */
#ifdef AGING_AGENT
        admin.agingAgent();                                          /* 老化する */
#endif
#ifdef MATING_AGENT
        admin.matingAgant();                                         /* 交配、出産する */
#endif

#ifdef RANDOM_LOCATE
        admin.relocateAgent();                                       /* 移動する */
#else
        admin.moveAgent();                                           /* 移動する */
#endif

        admin.contactAgent();                                        /* 近隣に接触する */
        admin.infectAgent();                                         /* 待機ウイルスを感染させる */
        admin.responseAgent();                                       /* 免疫応答（タグフリップ） */


        admin.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ; /* 出力：感染者 */
        admin.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ; /* 出力：免疫獲得者 */
        admin.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ; /* 出力：接触回数 */
        admin.outputFile_Population            ( "A_population.txt"       ) ; /* 出力：人口 */

        /* 途中経過 */
        LOG( monitor.getContactNum() );
        if( admin.getNumOfAgent() >= MAX_NUM_A ) break;              /* 最大エージェントを越えると終了 */
        if( monitor.getContactNum()==0 ) zero_count++;               /* １０回以上接触感染がなければ */
        if( zero_count >= 10 ) break;                                /* 強制的に終了する */
    }
    
    admin.outputFile_LastLog( "A_log.txt" );                         /* プログラムの初期設定など出力 */
    admin.printInitInfo();                                           /* 初期状態を表示 */

#ifdef __unix__
    Benchmark::Instance().stopTimer();                               /* ベンチマークの計測終了 */
    Benchmark::Instance().printTime();                               /* 計測時間表示 */
#endif

    // 確認用 -----------------------------------------------------------------
    // メモ
    // 計測時間出力
    LOG(sizeof(Agent));
    LOG(sizeof(Virus));
    LOG(sizeof(admin));
    return 0;
}
