/*
 * =====================================================================================
 *
 *       Filename:  AgentCounter.cpp
 *
 *    Description:  エージェント関連のカウンター
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU
 *
 * =====================================================================================
 */

#include "AgentCounter.h"

/*-----------------------------------------------------------------------------
 *  Instance()
 *-----------------------------------------------------------------------------*/
AgentCounter& AgentCounter :: Instance() {
    static AgentCounter singleton;
    return singleton;                                                /* インスタンスを返す */
}

void AgentCounter :: reset() {
  resetContact();
  resetInfectionContact();
}
