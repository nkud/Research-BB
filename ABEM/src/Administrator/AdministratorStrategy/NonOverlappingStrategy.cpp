/*
 * =====================================================================================
 *
 *       Filename:  NonOverlappingStrategy.cpp
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "AdministratorStrategy/NonOverlappingStrategy.h"

#include "Administrator.h"
#include "Landscape.h"
#include "Agent.h"
#include "Monitor.h"
#include "Function.h"

#include <string>

/*-----------------------------------------------------------------------------
 *
 *  NonOverlappingPopulation 戦略
 *
 *-----------------------------------------------------------------------------*/
void
NonOverlappingPopulation :: aging() {
  int die=0;
  ITERATOR(Agent *) it = ad_->getAgentIteratorBegin();               /* 先頭のエージェントから */
  while( it != ad_->getAgentIteratorEnd() ) {                        /* エージェントの末尾まで */
    (*it)->aging();                                                  /* 老化させる */
    if( (*it)->getAge() > A_MAX_AGE ) {                              /* もし寿命をこえたら */
      (*it)->resetParam();                                            /* 生まれ変わる */
      die++;
    }
    it++;                                                            /* 次のエージェントへ */
  }
}

void
NonOverlappingPopulation :: mating() {
  ITERATOR(Agent *) it_b = ad_->getAgentIteratorBegin();
  ITERATOR(Agent *) it_e = ad_->getAgentIteratorEnd();
  it_e--;
  while( it_b < it_e ) {
    (*it_b)->resetParam();
    (*it_e)->resetParam();
    it_b++;
    it_e--;
  }
  if(it_b==it_e) {
    (*it_b)->resetParam();
  }
}
