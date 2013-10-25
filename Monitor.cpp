/*
 * =====================================================================================
 *
 *       Filename:  Monitor.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Monitor.h"

Monitor& Monitor :: getInstance() {
    static Monitor coredata;
    return coredata;
}

void Monitor :: resetAll() {
    count_infection_contact_ = 0;
}
