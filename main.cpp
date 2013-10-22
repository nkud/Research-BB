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
    Virus virus;                                /* ウイルスは一個 */

    ofstream ofs("A_hasImmunity.dat");          /* 出力ファイル */

    int healthy = 0;                            /* 免疫獲得者カウンタ */

    FOR( i, TERM )                              /* 開始 */
    {
        FOR( j, NUM_A )                         /* エージェント全員に対して */
        {
            if( agent[j].hasImmunity( virus ) )     /* ウイルスに対して免疫獲得済みなら */
                continue;                       /* スキップ */
            agent[j].response( virus );             /* そうでないなら免疫応答 */
        }

        // CALCULATE
        healthy = 0;
        FOR( j, NUM_A )                         /* 免疫獲得者を計算 */
        {
            if( agent[j].hasImmunity( virus ) ) healthy++;
        }

        // OUTPUT
        ofs << i << SEPARATOR                   /* ファイルに出力 */
            << healthy << SEPARATOR             /* 免疫獲得者数 */
            << NUM_A - healthy << endl;         /* 免疫 未 獲得者数 */
    }

    return 0;
}
