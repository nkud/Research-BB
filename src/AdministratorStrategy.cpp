/* =============================================================================
 *
 *       Filename:  AdministratorStrategy.cpp
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * ========================================================================== */

#include "Administrator.h"
#include "Agent.h"
#include "AdministratorStrategy.h"

void NonOverlappingPopulation :: start( Administrator &ad ) {

//  ad.agingAgent();                                                   /* 老化する */
//  ad.moveAgent();                                                    /* 移動する */
//
//  ad.contactAgent();                                                 /* 近隣に接触する */
//  ad.infectAgent();                                                  /* 待機ウイルスを感染させる */
//  ad.responseAgent();                                                /* 免疫応答（タグフリップ） */
}

void Default :: aging(Administrator &ad) {
  ITERATOR(Agent *) it = ad.getAgentIteratorBegin();                 /* 先頭のエージェントから */
  while( it != ad.getAgentIteratorEnd() ) {                          /* エージェントの末尾まで */

    (*it)->aging();                                                  /* 老化させる */

    if( (*it)->getAge() > A_MAX_AGE ) {                              /* もし寿命をこえたら */
      ad.deleteAgent( it );                                          /* 生存配列から削除される */
    } else {
      it++;                                                          /* 次のエージェントへ */
    }
  }
}
void Default :: migrate(Administrator &ad) {

}
void Default :: contact(Administrator &ad) {

}
void Default :: infect(Administrator &ad) {

}
void Default :: response(Administrator &ad) {

}
void Default :: start(Administrator &ad) {

}
