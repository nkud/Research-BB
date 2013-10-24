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

const int TERM  = 50;                          // 期間 
const int NUM_V = 2;                            // ウイルスの種類 
const int NUM_A = 10000;                        // エージェントの数 

int main()
{
    srand((unsigned int)time(NULL)/2);          // 乱数初期化 

    Agent agent[ NUM_A ];                       // エージェントは複数 

    Virus virus[ NUM_V ] = {                    // ウイルス生成 
      // 123456789012345
        "110111001101100",
        "10011101101100"
    };

    int healthy0 = 0;                           // 免疫獲得者カウンタ 
    int healthy1 = 0;                           // 免疫獲得者カウンタ 
    int healthyAll = 0;                         // 免疫獲得者カウンタ 

    ofstream ofs("A_hasImmunity.dat");          // 出力ファイル 
    ofstream ofs_log("A_log.dat");          // 出力ファイル 

    /* Log */
    FOR(i, virus[0].len_) cout<<virus[0].tag_[i];cout<<endl;
    FOR(i, virus[1].len_) cout<<virus[1].tag_[i];cout<<endl;
    FOR(i, agent[0].len_) cout<<agent[0].tag_[i];cout<<" "<<agent[0].numOfVirus();cout<<endl;
    FOR(i, agent[1].len_) cout<<agent[1].tag_[i];cout<<" "<<agent[0].numOfVirus();cout<<endl;

    FOR( i, TERM )                              // 開始 
    {
/* log("----- new term"); */

        FOR( j, NUM_A )                         // エージェント全員に対して 
        {
            Virus &v = virus[ rand_array(NUM_V) ]; // ランダムにウイルスを選ぶ 
                                                // 感染確率は等しい 

            agent[j].infection( v );            // ウイルス v を感染させる
            agent[j].response();                // そうでないなら免疫応答 
        }

        /* CALCULATE */
        healthy0 = 0;                           // ウイルス０への免疫獲得者数
        healthy1 = 0;                           // ウイルス１への免疫獲得者数
        healthyAll = 0;                         // 全ウイルスへの免疫獲得者数
        FOR( j, NUM_A )                         // 免疫獲得者を計算 
        {
            if( agent[j].hasImmunity( virus[0] ) ) healthy0++;
            if( agent[j].hasImmunity( virus[1] ) ) healthy1++;
            if( agent[j].hasImmunity( virus[0] ) &&
                    agent[j].hasImmunity( virus[1] ) ) healthyAll++;
        }

        /* OUTPUT */
        ofs << i << SEPARATOR                   // ファイルに出力 
            << healthy0 << SEPARATOR            // 免疫獲得者数 
            << healthy1 << SEPARATOR            // 免疫獲得者数 
            << healthyAll << endl;              // 全免疫獲得者数 
    }

    /* --------------- */
    /* log */
    FOR(i, NUM_A) {
        FOR(j, agent[0].len_) ofs_log<<agent[i].tag_[j];
        ofs_log<<" "<<agent[i].numOfVirus();
        ofs_log<<" "<<agent[i].hasImmunity(virus[0]);
        ofs_log<<" "<<agent[i].hasImmunity(virus[1]);
        ofs_log<<endl;
    }
    /* --------------- */

    return 0;
}
