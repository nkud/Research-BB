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

const int TERM  = 30;                          /* 期間  */

int main()
{
    srand((unsigned int)time(NULL)/2);          /* 乱数初期化  */

    Agent agent[ NUM_A ];                       /* エージェントは複数  */
    AgentManager AM( agent );                   /* エージェントマネージャー */
                                                /* エージェントをまとめて動かす */

    Virus virus[ NUM_V ] = {                    /* ウイルス生成  */
      /* 123456789012345 */
        "1111110011",
        "1000111101"
    };

    int healthyAll = 0;                         /* 免疫獲得者カウンタ  */

    ofstream ofs("A_hasImmunity.dat");          /* 出力ファイル  */
    ofstream ofs_log("A_log.dat");              /* 出力ファイル  */

    // Log 
    virus[0].printTag();
    virus[1].printTag();
    agent[0].printTag();
    agent[1].printTag();

    FOR( i, TERM )                              /* 開始  */
    {
        FOR( j, NUM_A )                         /* エージェント全員に対して  */
        {
            Virus &v = virus[ rand_array(NUM_V) ]; /* ランダムにウイルスを選ぶ  */
                                                /* 感染確率は等しい  */

            agent[j].infection( v );            /* ウイルス v を感染させる */
            agent[j].response();                /* そうでないなら免疫応答  */
        }

        // CALCULATE 
        healthyAll = 0;                         /* 全ウイルスへの免疫獲得者数 */
        FOR( j, NUM_A )                         /* 免疫獲得者を計算  */
        {
            if( agent[j].hasImmunity( virus[0] ) &&
                    agent[j].hasImmunity( virus[1] ) ) healthyAll++;
        }

        // OUTPUT 
        ofs << i << SEPARATOR                   /* ファイルに出力  */
            << AM.numHasImmunity( virus[0] ) << SEPARATOR            /* 免疫獲得者数  */
            << AM.numHasImmunity( virus[1] ) << SEPARATOR            /* 免疫獲得者数  */
            << healthyAll << endl;              /* 全免疫獲得者数  */
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
