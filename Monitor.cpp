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
