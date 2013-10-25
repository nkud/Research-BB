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
// #include "Monitor.h"
#include "Administrator.h"

const int TERM  = 50;                           /* 期間  */

int main()
{
    srand((unsigned int)time(NULL)/2);          /* 乱数初期化  */

    Agent agent[ NUM_A ];                       /* エージェントは複数  */

    Virus virus[ NUM_V ] = {                    /* ウイルス生成  */
        /* 123456789012345 */
        "110111011",
        "100011100"
    };

    Landscape *landscape = new Landscape;       /* ランドスケープ初期化 */

    Administrator AD( agent, virus, landscape ); /* 管理者に登録 */

    int infected_all = 0;                         /* 免疫獲得者カウンタ  */

    ofstream ofs("A_hasImmunity.dat");          /* 出力ファイル  */
    ofstream ofs_log("A_log.dat");              /* 出力ファイル  */

    // Log 
    virus[0].printTag();
    virus[1].printTag();
    agent[0].printTag();
    agent[1].printTag();

    for(int i=0; i<10; i++) {
        agent[ i ].infection( virus[0] );
    }
    for(int i=10; i<20; i++) {
        agent[ i ].infection( virus[1] );
    }

    FOR( i, TERM )                              /* 開始  */
    {
        log("start");

        log("relocateAgent");
        AD.relocateAgent();                     /* 再配置 */

        log("contactAgent");
        AD.contactAgent();                      /* 感染 */

        log("responseAgent");
        AD.responseAgent();                     /* 免疫応答（タグフリップ） */

        // CALCULATE 
        infected_all = 0;                         /* 全ウイルスへの免疫獲得者数 */
        FOR( j, NUM_A )                         /* 免疫獲得者を計算  */
        {
            if( agent[j].isInfected( virus[0] ) &&
                    agent[j].isInfected( virus[1] ) ) infected_all++;
        }

        // OUTPUT 
        ofs << i << SEPARATOR                   /* ファイルに出力  */
            << AD.numIsInfected( virus[0] ) << SEPARATOR            /* 免疫獲得者数  */
            << AD.numIsInfected( virus[1] ) << SEPARATOR            /* 免疫獲得者数  */
            << infected_all << endl;              /* 全免疫獲得者数  */
    }

    // --------------- 
    // log 
    FOR(i, NUM_A) {
        FOR(j, agent[0].len_) ofs_log<<agent[i].tag_[j];
        ofs_log<<" "<<agent[i].numHoldingVirus();
        ofs_log<<" "<<agent[i].hasImmunity(virus[0]);
        ofs_log<<" "<<agent[i].hasImmunity(virus[1]);
        ofs_log<<endl;
    }
    // --------------- 

    return 0;
}
