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
    Agent agent[ MAX_NUM_A ];                              /* エージェントの集合  */
    Virus virus[ NUM_V ];                                  /* ウイルス生成 */
    Landscape *landscape = new Landscape;                  /* ランドスケープ初期化 */

    // 管理者に登録
    Administrator admin( agent, virus, landscape );

    Monitor &monitor = Monitor::Instance();                /* モニター */

    // 初期感染
    FOR( i, NUM_V ) {
        admin.initInfectAgentInRatio( virus[i], INIT_INFECTED_RATIO );            /* 感染させる */
    }

    monitor.generatePlotScript();                          /* XXX: gnuplot用 */

    int zero_count = 0;

    admin.relocateAgent();                                 /* ランダムに再配置 */
    /* 計測開始 */
    FOR( i, TERM )                                         /* 計算開始  */
    {
        break;
        log("------------ start");
        admin.incrementTerm();                             /* 期間を進める */

        monitor.resetAll();                                /* カウンターをリセット */

        admin.moveAgent();                                 /* 移動する */
        admin.contactAgent();                              /* 近隣に接触する */
        admin.infectAgent();                               /* 待機ウイルスを感染させる */
        admin.responseAgent();                             /* 免疫応答（タグフリップ） */

        /* 出力 */
        admin.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ;        /* 出力: ウイルスの保持状況 */
        admin.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ;
        admin.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ;

        /* 途中経過 */
        log( monitor.getContactNum() );
        log( agent[0].getX() );
        log( agent[0].getY() );
        if( monitor.getContactNum()==0 ) zero_count++;
        if( zero_count >= 10 ) break;
    }
    
    // 確認用 -----------------------------------------------------------------
    admin.printInitInfo();                                 /* 初期状態を表示 */

    // エージェントの最終的な状態など -----------------------------------------
    admin.outputFile_LastLog( "A_log.txt" );
    // ------------------------------------------------------------------------

    // 計測時間出力                             /* XXX: ??? */
    end = gettime();                                       /* 実行時間計測終了 */
    cout << end-start << endl;
    log(sizeof(Agent));
    log(sizeof(Virus));
    childbirth( agent[0], agent[1], agent[2] );
    agent[0].printTag();
    agent[1].printTag();
    agent[2].printTag();
    return 0;
}
