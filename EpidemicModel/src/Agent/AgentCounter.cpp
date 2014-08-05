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
#include "Agent.h"
#include "Function.h"
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
  resetRemoved();
}

///
/// calcAveValue
/// 	@note エージェントのタグ長平均を出力
double AgentCounter :: calcAveValue( VECTOR(Agent*)& agents ) {
  double sum = 0;
  double ave = 0;
  EACH( it_a, agents ) {
  	sum += (**it_a).getGene().value();
  }
  if( sum == 0 ) return 0;
  ave = (double)sum/(double)agents.size();
  return ave;
}