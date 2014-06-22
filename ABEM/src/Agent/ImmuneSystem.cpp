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

#include <vector>

/*-----------------------------------------------------------------------------
 *  isSusceptible()
 *-----------------------------------------------------------------------------*/
bool ImmuneSystem :: isSusceptible() {
  if( getVirusListSize() <= 0 )                                      /* 保持ウイルスが０ならば */
    return true;                                                     /* 感受性保持 */
  else                                                               /* そうでなければ */
    return false;                                                    /* 感染者 */
}
/*-----------------------------------------------------------------------------
 *  isIncubationPeriod()
 *-----------------------------------------------------------------------------*/
bool ImmuneSystem :: isIncubationPeriod() {
  if( isSusceptible() ) return false;                                /* 感受性保持者なら終了 */

  bool incubation_flag = false;                                      /* フラッグを設定 */
  EACH( it_v, getVirusList() ) {
    if( (*it_v)->isNonInfectiousPeriod() ) {                            /* 感染済みであれば */
      incubation_flag = true;
    } else {
      assert( (*it_v)->isInfectiousPeriod() or (*it_v)->isLethalPeriod() );
      return false;
    }
  }
  if( incubation_flag )
    return true;
  else
    return false;  
}
/*-----------------------------------------------------------------------------
 *  isSymptomaticPeriod()
 *      症候性期間であれば true
 *-----------------------------------------------------------------------------*/
bool ImmuneSystem :: isSymptomaticPeriod() {
  EACH( it_v, getVirusList() ) {
    if( (*it_v)->isInfectiousPeriod() ) {                                /* 感染済みであれば */
      return true;                                                   /* true を返す */
    }
  }
  return false;  
}
/*-----------------------------------------------------------------------------
 *  isLethal()
 *-----------------------------------------------------------------------------*/
bool ImmuneSystem :: isLethal() {
  EACH( it_v, getVirusList() )
  {
    if( (*it_v)->isLethalPeriod() ) {
      return true;
    }
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
    SAFE_DELETE(*it);
  }
  for( ITERATOR(Virus *) it = stand_by_virus_list_.begin(); it != stand_by_virus_list_.end(); it++ ) {
    SAFE_DELETE(*it);
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
void ImmuneSystem :: pushVirus( Virus& v, Agent& a ) {
  Virus *new_virus = new Virus( v );                                     /* 新しいウイルスデータを作成して */
  new_virus->setClingPoint( new_virus->searchStartPoint( a.getGene() ) );
  virus_list_.push_back( new_virus );
}
ITERATOR(Virus *) ImmuneSystem :: eraseVirus( ITERATOR(Virus *) it ) {
  SAFE_DELETE(*it);
  ITERATOR(Virus *) next = virus_list_.erase( it );                /* next iterator */
  return next;
}
bool ImmuneSystem :: hasNoVirus() const { if( virus_list_.empty() ) return true; else return false; }
ITERATOR(Virus *) ImmuneSystem :: getVirusListIteratorBegin() { return virus_list_.begin(); }
ITERATOR(Virus *) ImmuneSystem :: getVirusListIteratorEnd() { return virus_list_.end(); }
/* 待機ウイルスセット */
Virus *ImmuneSystem :: getStandByVirusAt( int n ) const { return stand_by_virus_list_.at(n); }
void ImmuneSystem :: pushStandByVirus( Virus& v ) {
  Virus *new_virus = new Virus( v );
  stand_by_virus_list_.push_back( new_virus );
}
int ImmuneSystem :: getStandByVirusListSize() const { return stand_by_virus_list_.size(); }
bool ImmuneSystem :: hasNoStandByVirus() const { return stand_by_virus_list_.empty(); }
ITERATOR(Virus *) ImmuneSystem :: getStandByVirusListIteratorBegin() { return stand_by_virus_list_.begin(); }
ITERATOR(Virus *) ImmuneSystem :: getStandByVirusListIteratorEnd() { return stand_by_virus_list_.end(); }
ITERATOR(Virus *) ImmuneSystem :: eraseStandByVirus( ITERATOR(Virus *) it ) {
  SAFE_DELETE(*it);
  ITERATOR(Virus *) next = stand_by_virus_list_.erase( it );       /* next iterator */
  return next;                                                        /* delete はしない  */
}
void ImmuneSystem :: clearStandByVirus() { stand_by_virus_list_.clear(); }

/*-----------------------------------------------------------------------------
 *  getCrisisVirusList()
 *-----------------------------------------------------------------------------*/
VECTOR(Virus *) ImmuneSystem :: getCrisisVirusList() {
  VECTOR(Virus *) crisis_virus;
  EACH( it_v, getVirusList() )
  {
    if( (*it_v)->isInfectiousPeriod() )
    {
      crisis_virus.push_back( *it_v );
    }
  }
  return crisis_virus;
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
    if( self.getImmuneSystem().getVirusListSize() >= A_MAX_V_CAPACITY ) { /* 最大値を越えてたら */
    return false;                                                    /* 感染せずに終了 */
  }
  EACH( it_v, getVirusList() ) 
  {
    if( (**it_v) == v ) {
      // XXX: あってる？？有効？？
      assert( (*it_v)->isEqualTo(v) );
      assert( (**it_v).getGene().hamDistance( v.getGene(), 0) == 0 );
      return false;                                                  /* 感染せずに終了 */
    }
  }
  if( self.hasImmunity( v ) ) {                                      /* 免疫獲得済みなら  */
    return false;                                                    /* 感染せずに終了 */
  }

//  Virus *new_v = new Virus( v );                                      /* 新しいウイルスデータを作成して */
//  new_v->setClingPoint( new_v->searchStartPoint( self.getGene() ) );
  // XXX: ウイルスの関数にする setClingPoint( Tag * );
  self.getImmuneSystem().pushVirus( v, self );                   /* 保持ウイルスリストに追加する */

  AgentCounter::Instance().countUpInfectionContact();

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
  if( self.getImmuneSystem().hasNoVirus() ) {                       /* 感染していなければ */
    self.getImmuneSystem().resetInfectionTime();                    /* 感染期間は０で */
    return 0;                                                        /* 終了する */
  }

  ITERATOR(Virus *) it_v
    = self.getImmuneSystem().getVirusListIteratorBegin();           /* 先頭のウイルスに対し */

  if( ! self.hasImmunity( **it_v ) ) {                                 /* 免疫を獲得していなければ */
    self.getGene().flipToGeneAtPosition( (*it_v)->getGene(), (*it_v)->getClingPoint() );
  }

  if( self.hasImmunity( **it_v ) )                                     /* そのウイルスに対して */
  {                                                                  /* 免疫獲得すれば */
    // XXX: 要検討
    it_v = self.getImmuneSystem().eraseVirus( it_v );                   /* 保持ウイルスから v(先頭) を削除 */
  }
  return self.getImmuneSystem().getInfectionTime();
}

int ImmuneSystem :: progressDisease() {
  // 突然変異
  EACH( it_v, getVirusList() )
  {
    (*it_v)->incrementInfectionTime();                               /* 感染期間を増やす */
    if( (*it_v)->isInfectiousPeriod() ) {                            /* ウイルスが潜伏期間なら */
      (*it_v)->mutation( (*it_v)->getMutationRate() );               /* 突然変異を確率で起こす */
    }
  }
  // 感染期間を増やす
  if( getVirusListSize() > 0 ) {             /* まだ感染していれば */
    incrementInfectionTime();                /* 総感染期間を増やして */
  } else {                                                           /* そうでなければ */
    resetInfectionTime();                    /* 感染期間を０にリセット */
  }
  return getInfectionTime();                 /* 総染期間を返す */
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
