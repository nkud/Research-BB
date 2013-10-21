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

const int TERM = 10;

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
            log(&a);
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
    // --------------------------------
//    FOR(j, 10)
//    {
//        FOR(i,TAG_LEN_A) cout << a[0].tag_[i]; cout << endl;
//        FOR(i,TAG_LEN_V) cout << v.tag_[i]; cout << endl;
//        log( a[0].hasImmunity( v ) );
//        if( !a[0].hasImmunity( v ) )
//        {
//            a[0].response(v);
//        }
//    }
    log( "---" );
    log( sizeof( Agent ) );
    log( sizeof( Virus ) );
    log( sizeof( __TagInterface ) );

    return 0;
}
