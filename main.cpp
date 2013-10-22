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
#include <string>
#include <fstream>
using namespace std;

#include "Global.h"
#include "Function.h"
#include "Agent.h"
#include "Virus.h"

const int TERM = 20;                            /* 期間 */

int main()
{
    srand((unsigned int)time(NULL)/2);          /* 乱数初期化 */

    Agent agent[ NUM_A ];                       /* エージェントは複数 */
    Virus virus[ NUM_V ];                       /* ウイルスは一個 */

    int healthy0 = 0;                            /* 免疫獲得者カウンタ */
    int healthy1 = 0;                            /* 免疫獲得者カウンタ */
    int healthy2 = 0;                            /* 免疫獲得者カウンタ */
    int healthyAll = 0;                            /* 免疫獲得者カウンタ */

    ofstream ofs("A_hasImmunity.dat");          /* 出力ファイル */

    FOR( i, TERM )                              /* 開始 */
    {
        log("----- new term");
        FOR( j, NUM_A )                         /* エージェント全員に対して */
        {
            Virus &v = virus[ rand_array(NUM_V) ]; /* ランダムにウイルスを選ぶ */
                                                /* 感染確率は等しい */

            agent[j].infection( v );
//            if( agent[j].hasImmunity( v ) ) {    /* ウイルスに対して免疫獲得済みなら */
//                continue;                       /* スキップ */
//            }
            agent[j].response();                /* そうでないなら免疫応答 */
        }

        // CALCULATE
        healthy0 = 0;
        healthy1 = 0;
        healthy2 = 0;
        healthyAll = 0;
        FOR( j, NUM_A )                         /* 免疫獲得者を計算 */
        {
            if( agent[j].hasImmunity( virus[0] ) ) healthy0++;
            if( agent[j].hasImmunity( virus[1] ) ) healthy1++;
            if( agent[j].hasImmunity( virus[2] ) ) healthy2++;
            if( agent[j].hasImmunity( virus[0] ) &&
                    agent[j].hasImmunity( virus[1] ) &&
                    agent[j].hasImmunity( virus[2] ) ) healthyAll++;
        }

        // OUTPUT
        ofs << i << SEPARATOR                   /* ファイルに出力 */
            << healthy0 << SEPARATOR            /* 免疫獲得者数 */
            << healthy1 << SEPARATOR            /* 免疫獲得者数 */
            << healthy2 << SEPARATOR            /* 免疫獲得者数 */
            << healthyAll << endl;              /* ALL免疫獲得者数 */
    }

    FOR(i, TAG_LEN_V) cout<<virus[0].tag_[i];cout<<endl;
    FOR(i, TAG_LEN_V) cout<<virus[1].tag_[i];cout<<endl;
    FOR(i, TAG_LEN_V) cout<<virus[2].tag_[i];cout<<endl;

    return 0;
}
