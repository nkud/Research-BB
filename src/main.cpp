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

double gettime() {                                         /* ベンチマーク */
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main()
{
    double start, end;                                     /* タイマー */
    start = gettime();                                     /* 実行時間計測開始 */

    srand( (unsigned int)time(NULL)/2 );                   /* 乱数初期化  */

    // 初期化
    Agent agent[ NUM_A ];                                  /* エージェントの集合  */
    Virus virus[ NUM_V ] =
    {                                                      /* ウイルス生成 */
//        *( new Virus(5, 0.60 )),                           /* タグ長、感染確率 */
//        *( new Virus(10, 0.60 )),                          /* タグ長、感染確率 */
//        *( new Virus(15, 0.60 ))
    };
    Landscape *landscape = new Landscape;                  /* ランドスケープ初期化 */

    // 管理者に登録
    Administrator AD( agent, virus, landscape );

    Monitor &monitor = Monitor::Instance();                /* モニター */

    // 初期感染
    FOR( i, NUM_V ) {
        AD.initInfectAgentInRatio( virus[i], INIT_INFECTED_RATIO );            /* 感染させる */
    }

    int initial_num_a = AD.numHasVirus( virus[0] );        /* 記録しておく */
    int initial_num_b = AD.numHasVirus( virus[1] );

    monitor.generatePlotScript();                          /* XXX: gnuplot用 */

    int zero_count = 0;
    /* 計測開始 */
    FOR( i, TERM )                                         /* 計算開始  */
    {
        log("------------ start");

        monitor.resetAll();                                /* カウンターをリセット */

        AD.relocateAgent();                                /* ランダムに再配置 */
        AD.contactAgent();                                 /* 近隣に接触する */
        AD.infectAgent();                                  /* 待機ウイルスを感染させる */
        AD.responseAgent();                                /* 免疫応答（タグフリップ） */

        /* 出力 */
        AD.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ;        /* 出力: ウイルスの保持状況 */
        AD.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ;
        AD.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ;

        log( monitor.getContactNum() );
        if( monitor.getContactNum()==0 ) zero_count++;
        if( zero_count >= 10 ) break;
    }
    
    // 確認用 -----------------------------------------------------------------
    AD.printInitInfo();                                        /* 初期状態を表示 */

    // エージェントの最終的な状態など -----------------------------------------
    AD.outputFile_LastLog( "A_log.txt" );
    // ------------------------------------------------------------------------

    // 計測時間出力                             /* XXX: ??? */
    end = gettime();                                       /* 実行時間計測終了 */
    cout << end-start << endl;
    log(sizeof(Agent));
    log(sizeof(Virus));
    return 0;
}
