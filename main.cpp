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
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

#include "Global.h"
#include "Function.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"
#include "Monitor.h"
#include "Administrator.h"

#define HAS_VIRUS_FNAME     "A_hasVirus.dat"

const int TERM  = 500;                          /* 期間  */

int main()
{
    srand((unsigned int)time(NULL)/2);          /* 乱数初期化  */

    // 初期化
    Agent agent[ NUM_A ];                       /* エージェントの集合  */
    Virus virus[ NUM_V ] = {                    /* ウイルス生成  */
        15,                                     /* 長さ、タグなど初期化 */
        12
//        "01010110",
//        "10000110"
    };
    Landscape *landscape = new Landscape;       /* ランドスケープ初期化 */

    Administrator AD( agent, virus, landscape ); /* 管理者に登録 */

    AD.initInfectAgentInRatio( virus[0], 0.1 ); /* 感染させる */
    AD.initInfectAgentInRatio( virus[1], 0.5 );

    Monitor::getInstance().resetAll();          /* モニターのカウンターをリセット */

    /* 計測開始 */
    FOR( i, TERM )                              /* 計算開始  */
    {
        log("------------ start");

        Monitor::getInstance().resetAll();      /* カウンターをリセット */
        Monitor::getInstance().count_infection_contact_ = 0; /* XXX: 関数化 */

        AD.relocateAgent();                     /* ランダムに再配置 */
        AD.contactAgent();                      /* 近隣に感染させる */
        AD.responseAgent();                     /* 免疫応答（タグフリップ） */

        /* 出力 */
        AD.outputFile_HasVirus( HAS_VIRUS_FNAME ); /* 出力: ウイルスの保持状況 */

        log( Monitor::getInstance().count_infection_contact_ );
    }

    Monitor::getInstance().generatePlotScript();  /* gnuplot用スクリプト */
    
    FOR( i, NUM_V ) virus[ i ].printTag();      /* 全ウイルスのタグを表示 */

    // エージェントの最終的な状態
    ofstream ofs_log("A_log.dat");              /* 出力ファイル  */
    FOR(i, NUM_A) {
        FOR(j, agent[0].len_) ofs_log<<agent[i].tag_[j];
        ofs_log<<" "<<agent[i].numHoldingVirus();
        ofs_log<<endl;
    }

    return 0;
}
