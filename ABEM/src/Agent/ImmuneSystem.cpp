/*
 * =====================================================================================
 *
 *       Filename:  ImmuneSystem.cpp
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Agent.h"
#include "AgentCounter.h"
#include "Gene.h"
#include "AgentStrategy.h"
#include "Function.h"
#include "VirusCounter.h"
#include "Config.h"

#include <vector>

bool ImmuneSystem :: isIncubation() {
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    if( (*it_v)->isIncubationPeriod() ) {                                            /* 感染済みであれば */
      return true;                                                   /* true を返す */
    }
    it_v++;                                                          /* 次のウイルスリストへ */
  }
  return false;  
}
bool ImmuneSystem :: isCrisis() {
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    if( (*it_v)->isCrisisPeriod() or (*it_v)->isLethalPeriod() ) {   /* 感染済みであれば */
      return true;                                                   /* true を返す */
    }
    it_v++;                                                          /* 次のウイルスリストへ */
  }
  return false;  
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: ImmuneSystem
 * Description:  コンストラクタ
 *--------------------------------------------------------------------------------------
 */
ImmuneSystem :: ImmuneSystem() :
  infection_time_( 0 )
{
}
/*-----------------------------------------------------------------------------
 *  ImmuneSystem :: ~ImmuneSystem
 *-----------------------------------------------------------------------------*/
ImmuneSystem :: ~ImmuneSystem() {
  for( ITERATOR(Virus *) it = virus_list_.begin(); it != virus_list_.end(); it++ ) {
    delete (*it);
  }
  for( ITERATOR(Virus *) it = stand_by_virus_list_.begin(); it != stand_by_virus_list_.end(); it++ ) {
    delete (*it);
  }
  virus_list_.clear();
  stand_by_virus_list_.clear();
}
/*-----------------------------------------------------------------------------
 *
 *  ウイルス操作セット
 *
 *-----------------------------------------------------------------------------*/
/* 保持ウイルスセット */
Virus *ImmuneSystem :: getVirusAt( int n ) const { return virus_list_.at( n ); }
int ImmuneSystem :: getVirusListSize() const { return virus_list_.size(); }
void ImmuneSystem :: pushVirus( Virus *v ) { virus_list_.push_back( v ); }
ITERATOR(Virus *) ImmuneSystem :: eraseVirus( ITERATOR(Virus *) it ) {
  delete (*it);
  ITERATOR(Virus *) next = virus_list_.erase( it );                /* next iterator */
  return next;
}
bool ImmuneSystem :: hasNoVirus() const { if( virus_list_.empty() ) return true; else return false; }
ITERATOR(Virus *) ImmuneSystem :: getVirusListIteratorBegin() { return virus_list_.begin(); }
ITERATOR(Virus *) ImmuneSystem :: getVirusListIteratorEnd() { return virus_list_.end(); }
/* 待機ウイルスセット */
Virus *ImmuneSystem :: getStandByVirusAt( int n ) const { return stand_by_virus_list_.at(n); }
void ImmuneSystem :: pushStandByVirus( Virus *v ) { stand_by_virus_list_.push_back( v ); }
int ImmuneSystem :: getStandByVirusListSize() const { return stand_by_virus_list_.size(); }
bool ImmuneSystem :: hasNoStandByVirus() const { return stand_by_virus_list_.empty(); }
ITERATOR(Virus *) ImmuneSystem :: getStandByVirusListIteratorBegin() { return stand_by_virus_list_.begin(); }
ITERATOR(Virus *) ImmuneSystem :: getStandByVirusListIteratorEnd() { return stand_by_virus_list_.end(); }
ITERATOR(Virus *) ImmuneSystem :: eraseStandByVirus( ITERATOR(Virus *) it ) {
  ITERATOR(Virus *) next = stand_by_virus_list_.erase( it );       /* next iterator */
  return next;                                                        /* delete はしない  */
}
void ImmuneSystem :: clearStandByVirus() { stand_by_virus_list_.clear(); }

int ImmuneSystem :: getOnSetVirusListSize() {
  int ret = 0;
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    // if( (*it_v)->getInfectionTime() > V_INCUBATION_PERIOD ) {
    if( (*it_v)->isCrisisPeriod() ) {
      ret++;
    }
    it_v++;                                                          /* 次のウイルスリストへ */
  }
  return ret;
}
Virus *ImmuneSystem :: getOnSetVirusAt( int n ) {
  int num = 0;
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    // if( num == n and (*it_v)->getInfectionTime() > V_INCUBATION_PERIOD ) {
    if( num == n and (*it_v)->isCrisisPeriod() ) {
      return (*it_v);
    }
    it_v++;                                                          /* 次のウイルスリストへ */
    num++;
  }
  return (*it_v);
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: hasVirus( Virus & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
bool ImmuneSystem :: hasVirus( Virus &v ) {
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    if( (*it_v)->isEqualTo( v ) ) {                                            /* 感染済みであれば */
      return true;                                                   /* true を返す */
    }
    it_v++;                                                          /* 次のウイルスリストへ */
  }
  return false;                                                      /* 未感染なので false を返す */
}
bool ImmuneSystem :: hasVirus() const {
  if( getVirusListSize() > 0 ) {
    return true;
  } else {
    return false; 
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: infection( Tag & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool ImmuneSystem :: infection( Agent &self, Virus &v )
{
  // return immunesystem_strategy_->infection(self, v);
    if( self.getImmuneSystem()->getVirusListSize() >= A_MAX_V_CAN_HAVE ) { /* 最大値を越えてたら */
    // A_MAX_V_CAPACITY
    return false;                                                    /* 感染せずに終了 */
  }
  ITERATOR(Virus *) it_v = self.getImmuneSystem()->getVirusListIteratorBegin(); /* 保持ウイルスリストを取得 */
  while( it_v != self.getImmuneSystem()->getVirusListIteratorEnd() ) { /* 既に保持しているウイルスなら */
    if( (*it_v)->isEqualTo( v ) ) {
      // XXX: あってる？？有効？？
      return false;                                                  /* 感染せずに終了 */
    }
    it_v++;                                                          /* 次の保持ウイルス */
  }
  if( self.hasImmunity( v ) ) {                                      /* 免疫獲得済みなら  */
    return false;                                                    /* 感染せずに終了 */
  }
//  Virus *new_v                                                   /* 新しいウイルスデータを作成して */
//    = new Virus( v, v.searchStartPoint( *self.getTag() ), 0 );
  Virus *new_v = new Virus( &v );
  new_v->setClingPoint( new_v->searchStartPoint( *self.getGene() ) );
  // XXX: ウイルスの関数にする setClingPoint( Tag * );
  self.getImmuneSystem()->pushVirus( new_v );                        /* 保持ウイルスリストに追加する */

  AgentCounter::Instance().countUpInfectionContact();
//  Monitor::Instance().countUpInfectionContact(vdata->v_);          /* 感染のために接触した回数を増やす */
  return true;                                                       /* 感染して true を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: response( Tag & )
 * Description:  先頭のウイルスに対する免疫を獲得するまで、
 *               １期間に１つタグをフリップさせていく。
 *--------------------------------------------------------------------------------------
 */
int ImmuneSystem :: response( Agent &self )
{
  // return immunesystem_strategy_->response(self);
    if( self.getImmuneSystem()->hasNoVirus() ) {                       /* 感染していなければ */
    self.getImmuneSystem()->resetInfectionTime();                    /* 感染期間は０で */
    return 0;                                                        /* 終了する */
  }

  ITERATOR(Virus *) it_v
    = self.getImmuneSystem()->getVirusListIteratorBegin();           /* 先頭のウイルスに対し */

  if( ! self.hasImmunity( **it_v ) ) {                                 /* 免疫を獲得していなければ */
    // flip_once(                                                       /* ひとつフリップする */
    //     self.getGene()->getTag()+(*it_v)->getClingPoint(),
    //     (*it_v)->getGene()->getTag(),
    //     (*it_v)->getLen() );
    self.getGene()->flipToGeneAtPosition( (*it_v)->getGene(), (*it_v)->getClingPoint() );
  }

  if( self.hasImmunity( **it_v ) )                                     /* そのウイルスに対して */
  {                                                                  /* 免疫獲得すれば */
    // XXX: 要検討
    it_v = self.getImmuneSystem()->eraseVirus( it_v );                   /* 保持ウイルスから v(先頭) を削除 */
  }

  // 突然変異
  ITERATOR( Virus * ) it_vv                                           /* 先頭のウイルスデータから */
    = self.getImmuneSystem()->getVirusListIteratorBegin();
  while( it_vv != self.getImmuneSystem()->getVirusListIteratorEnd() ) /* 末尾まで */
  {
    (*it_vv)->incrementInfectionTime();                               /* 感染期間を増やす */
    if( (*it_vv)->isCrisisPeriod() ) {                            /* ウイルスが潜伏期間なら */
      (*it_vv)->mutation( (*it_vv)->getMutationRate() );                            /* 突然変異を確率で起こす */
    }
    it_vv++;                                                          /* 増やす */
  }
  // 感染期間を増やす
  if( self.getImmuneSystem()->getVirusListSize() > 0 ) {             /* まだ感染していれば */
    self.getImmuneSystem()->incrementInfectionTime();                /* 総感染期間を増やして */
  } else {                                                           /* そうでなければ */
    self.getImmuneSystem()->resetInfectionTime();                    /* 感染期間を０にリセット */
  }
  return self.getImmuneSystem()->getInfectionTime();                 /* 総染期間を返す */
}

/*-----------------------------------------------------------------------------
 *  ImmuneSystem :: incrementInfectionTime()
 *      感染期間を増やす
 *-----------------------------------------------------------------------------*/
void ImmuneSystem :: incrementInfectionTime() {
  assert( infection_time_ >= 0 );
  infection_time_++;
}
int ImmuneSystem :: getInfectionTime() const {
  /*-----------------------------------------------------------------------------
   *  感染期間を返す
   *-----------------------------------------------------------------------------*/
  return infection_time_;
}
void ImmuneSystem :: resetInfectionTime() {
  /*-----------------------------------------------------------------------------
   *  感染期間を０にリセットする
   *-----------------------------------------------------------------------------*/
  infection_time_ = 0;
}