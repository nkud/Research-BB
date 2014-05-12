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
void NonOverlappingPopulation :: initAgent() {
  RandomWalk *random_walk = new RandomWalk( 1 );
  Relocate *relocate = new Relocate;
  __ChildBirthStrategy *cbs = new CoupleTag;
  FOR( i, A_INIT_NUM ) {                                             /* 初期エージェントの数だけ */
    ad_->agent()->push_back(
        new Agent( random_walk, cbs, 20 ) );                                 /* ランダムウォーク */
  }
//  ITERATOR(Agent *) it = ad_->getAgentIteratorBegin();               /* 先頭のエージェントから */
//  while( it != ad_->getAgentIteratorEnd() ) {                        /* エージェントの末尾まで */
//    (*it)->setAge(0);
//    it++;
//  }
}

//void
//NonOverlappingPopulation :: oneDay() {
//  ad_->agingAgent();                                                   /* 老化する */
//  ad_->moveAgent();                                                    /* 移動する */
//
//  ad_->contactAgent();                                                 /* 近隣に接触する */
//  ad_->infectAgent();                                                  /* 待機ウイルスを感染させる */
//  ad_->responseAgent();                                                /* 免疫応答（タグフリップ） */
//}

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
  // 死亡人数を表示
  LOG(die);
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
