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

#include "Agent.cpp"
#include "Virus.cpp"

#include <iostream>
using namespace std;

int main()
{
    Agent a(10);
    Virus v(3);

    cout << "start" << endl;
    cout << a.tag_[0] << endl;
    cout << "end" << endl;

    return 0;
}
