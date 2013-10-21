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
#include "Global.h"
#include "Function.h"

#include "Agent.h"
#include "Virus.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int TERM = 20;

int main()
{
    srand((unsigned int)time(NULL)/2);                          /* 乱数初期化 */

    Agent agent[ NUM_A ];
    Virus virus;

    ofstream ofs("A_hasImmunity.dat");

    int healthy = 0;

    FOR( i, TERM )
    {
        FOR( j, NUM_A )
        {
            Agent &a = agent[ j ];
            if( a.hasImmunity( virus ) )
                continue;
            a.response( virus ); 
        }
        healthy = 0;
        FOR( j, NUM_A )
        {
            if( agent[j].hasImmunity( virus ) ) healthy++;
        }
        ofs << i << SEPARATOR
            << healthy << SEPARATOR
            << NUM_A - healthy << endl;
    }

    return 0;
}
