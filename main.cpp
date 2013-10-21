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
using namespace std;

int main()
{
    srand((unsigned int)time(NULL)/2);                          /* 乱数初期化 */

    Agent a ( TAG_LEN_A ) ;
    Virus v ( TAG_LEN_V  ) ;

    // --------------------------------
    cout << "start" << endl;

    FOR(j, 10)
    {
        FOR(i,TAG_LEN_A) cout << a.tag_[i]; cout << endl;
        FOR(i,TAG_LEN_V) cout << v.tag_[i]; cout << endl;
        log( a.hasImmunity( v ) );
        if( !a.hasImmunity( v ) )
        {
            a.response(v);
        }
    }
    log( "---" );
    log( sizeof( Agent ) );
    log( sizeof( Virus ) );
    log( sizeof( __TagInterface ) );

    cout << "end" << endl;

    return 0;
}
