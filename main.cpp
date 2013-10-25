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
      // 1234567890
        "11010101",
        "10001011"
    };
    Landscape *landscape = new Landscape;       /* ランドスケープ初期化 */

    Administrator AD( agent, virus, landscape ); /* 管理者に登録 */

    ofstream ofs("A_hasVirus.dat");             /* 出力ファイル  */
    ofstream ofs_log("A_log.dat");              /* 出力ファイル  */


    AD.initInfectAgentInRatio( virus[0], 0.8 );   /* 感染させる */
    AD.initInfectAgentInRatio( virus[1], 0.1 );

    Monitor::getInstance().resetAll();
    log(Monitor::getInstance().count_infection_contact_);

    FOR( i, TERM )                              /* 開始  */
    {
        log("------------ start");
        Monitor::getInstance().resetAll();
        Monitor::getInstance().count_infection_contact_ = 0;

        AD.relocateAgent();                     /* ランダムに再配置 */
        AD.contactAgent();                      /* 感染 */
        AD.responseAgent();                     /* 免疫応答（タグフリップ） */

        // OUTPUT 
        ofs << i << SEPARATOR                   /* ファイルに出力 */
            << AD.numHasVirus( virus[0] ) << SEPARATOR            /* ウイルス０保持者 */
            << AD.numHasVirus( virus[1] ) << SEPARATOR            /* ウイルス１保持者 */
            << AD.numHasAllVirus() << endl;     /* 全ウイルス保持者 */
        log(Monitor::getInstance().count_infection_contact_);
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
