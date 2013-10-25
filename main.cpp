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

const int TERM  = 100;                           /* 期間  */

int main()
{
    srand((unsigned int)time(NULL)/2);          /* 乱数初期化  */

    // 初期化
    Agent agent[ NUM_A ];                       /* エージェントは複数  */
    Virus virus[ NUM_V ] = {                    /* ウイルス生成  */
      // 123456789
        "1101001",
        "1000100110"
    };
    Landscape *landscape = new Landscape;       /* ランドスケープ初期化 */

    Administrator AD( agent, virus, landscape ); /* 管理者に登録 */

    ofstream ofs("A_hasVirus.dat");             /* 出力ファイル  */
    ofstream ofs_log("A_log.dat");              /* 出力ファイル  */


    for(int i=0; i<1000; i++) {                   /* 感染させる */
        agent[ i ].infection( virus[0] );
    }
    for(int i=10; i<15; i++) {
        agent[ i ].infection( virus[1] );
    }


    FOR( i, TERM )                              /* 開始  */
    {
        log("------------ start");
        log(agent[0].x_);
        log(agent[0].numHoldingVirus());

        AD.relocateAgent();                     /* ランダムに再配置 */
        AD.contactAgent();                      /* 感染 */
        AD.responseAgent();                     /* 免疫応答（タグフリップ） */

        // OUTPUT 
        ofs << i << SEPARATOR                   /* ファイルに出力 */
            << AD.numHasVirus( virus[0] ) << SEPARATOR            /* ウイルス０保持者 */
            << AD.numHasVirus( virus[1] ) << SEPARATOR            /* ウイルス１保持者 */
            << AD.numHasAllVirus() << endl;     /* 全ウイルス保持者 */
    }

    // log
    FOR(i, NUM_A) {
        FOR(j, agent[0].len_) ofs_log<<agent[i].tag_[j];
        ofs_log<<" "<<agent[i].numHoldingVirus();
        ofs_log<<endl;
    }
    //
    return 0;
}
