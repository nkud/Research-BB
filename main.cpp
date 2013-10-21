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
using namespace std;

int main()
{
    srand(time(NULL));                          /* 乱数初期化 */

    Agent a ( 10 ) ;
    Virus v ( 3  ) ;

    // --------------------------------
    cout << "start" << endl;
    cout << a.tag_[0] << endl;
    cout << a.tag_[1] << endl;
    cout << "end" << endl;

    return 0;
}
