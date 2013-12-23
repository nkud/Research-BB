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
#include "FileFactory.h"


/*-----------------------------------------------------------------------------
 *
 *  メインルーチン
 *
 *-----------------------------------------------------------------------------*/
int main()
{
#ifdef __unix__
    Benchmark::Instance().startTimer();                              /* ベンチマーク計測開始 */
#endif
    srand( (unsigned int)time(NULL)/2 );                             /* 乱数初期化 */

    /*-----------------------------------------------------------------------------
     *  初期化
     *-----------------------------------------------------------------------------*/
    /* エージェント */
    VECTOR(Agent *) agent;                                           /* エージェントの配列 */
    FOR( i, INIT_NUM_A ) {                                           /* 初期エージェントの数だけ */
        agent.push_back( new Agent );                                /* エージェントを初期化 */
    }
    /* ウイルス */
    VECTOR(Virus *) virus;
//    virus.push_back( new Virus( 16, new Normal ) );                  /* 通常ウイルスを追加 */
//    virus.push_back( new Virus( 16, new Normal ) );                  /* 通常ウイルスを追加 */
    virus.push_back( new Virus( 8, new Fixed(0) ) );                /* 固定ウイルスを追加 */
    virus.push_back( new Virus( 8, new Fixed(0) ) );               /* 固定ウイルスを追加 */
    /* 土地 */
    Landscape landscape;                                             /* ランドスケープ初期化 */

    /* 管理者 */
    Administrator admin( agent, virus, &landscape );                 /* 管理者に登録 */

    /* モニター・ファイル生成クラス */
    Monitor &monitor = Monitor::Instance();                          /* モニター */
    FileFactory &ff = FileFactory::Instance();                       /* 出力ファイルを管理 */
    ff.setAdministrator( admin );                                    /* 管理者を登録 */

    /*-----------------------------------------------------------------------------
     *  エージェントへの初期動作
     *-----------------------------------------------------------------------------*/
    /* エージェントへの初期感染 */
    FOR( i, NUM_V ) {
        admin.initInfectAgentInRatio( *virus[i], INIT_INFECTED_RATIO );            /* 初期感染させる */
    }
    /* 土地にランダムに配置 */
    admin.relocateAgent();                                           /* ランダムに配置 */

    int zero_count = 0;                                              /* 感染接触が起こらなかった数をカウント */
                                                                     /* 10回になると、計算を強制終了させる */

    /*-----------------------------------------------------------------------------
     *  計算開始
     *-----------------------------------------------------------------------------*/
    FOR( i, TERM )                                                   /* 計算開始  */
    {
        cout << "===================================" << endl;
        LOG( i );

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

        /* 経過出力 */
        ff.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ; /* 出力：感染者 */
        ff.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ; /* 出力：免疫獲得者 */
        ff.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ; /* 出力：接触回数 */
        ff.outputFile_Population            ( "A_population.txt"       ) ; /* 出力：人口 */
        LOG( monitor.getContactNum() );

        /* 強制終了 */
        if( monitor.getContactNum()==0 ) zero_count++;               /* １０回以上接触感染がなければ */
        if( zero_count >= 10 ) break;                                /* 強制的に終了する */
    }

    /*-----------------------------------------------------------------------------
     *  計算終了
     *-----------------------------------------------------------------------------*/
    
    ff.outputFile_LastLog( "Log.txt" );                              /* プログラムの初期設定など出力 */
    admin.printInitInfo();                                           /* 初期状態を表示 */

#ifdef __unix__
    Benchmark::Instance().stopTimer();                               /* ベンチマークの計測終了 */
    Benchmark::Instance().printTime();                               /* 計測時間表示 */
#endif

    ff.generateResultHtml(admin.getTerm());                          /* 結果表示用HTMLファイル出力 */
    ff.generatePlotScriptForPng();                                   /* gnuplot用ファイル出力 */

    // 確認用 -----------------------------------------------------------------
    // メモ
    // 計測時間出力
    LOG(sizeof(Agent));
    LOG(sizeof(Virus));
    LOG(sizeof(admin));
    return 0;
}