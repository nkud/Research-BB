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
#include "Tag.h"
#include "AgentStrategy.h"
#include "Function.h"

#include <vector>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: ImmuneSystem
 * Description:  コンストラクタ
 *--------------------------------------------------------------------------------------
 */
ImmuneSystem :: ImmuneSystem() :
  infection_time_( 0 )
{
  virus_list_ = new std::vector<Virus *>;
  stand_by_virus_list_ = new std::vector<Virus *>;
  immunesystem_strategy_ = new TagFlip();
}
ImmuneSystem :: ~ImmuneSystem() {
  while( virus_list_->size() > 0 ) {
    ITERATOR(Virus *) temp = virus_list_->begin();
    delete *temp;
    virus_list_->erase(temp);
  }
  while( stand_by_virus_list_->size() > 0 ) {
    ITERATOR(Virus *) temp = stand_by_virus_list_->begin();
    delete *temp;
    stand_by_virus_list_->erase(temp);
  }
  assert( virus_list_ != NULL );
  assert( stand_by_virus_list_ != NULL );
  assert( immunesystem_strategy_ != NULL );
  delete virus_list_;
  delete stand_by_virus_list_;
  delete immunesystem_strategy_;
}
/*-----------------------------------------------------------------------------
 *
 *  ウイルス操作セット
 *
 *-----------------------------------------------------------------------------*/
/* 保持ウイルスセット */
Virus *ImmuneSystem :: getVirusAt( int n ) const { return (*virus_list_).at( n ); }
int ImmuneSystem :: getVirusListSize() const { return (*virus_list_).size(); }
void ImmuneSystem :: pushVirus( Virus *v ) { (*virus_list_).push_back( v ); }
void ImmuneSystem :: eraseVirus( std::vector<Virus *>::iterator it ) { delete (*it); (*virus_list_).erase( it ); }
bool ImmuneSystem :: hasNoVirus() const { if( (*virus_list_).empty() ) return true; else return false; }
std::vector<Virus *>::iterator ImmuneSystem :: getVirusListIteratorBegin() { return (*virus_list_).begin(); }
std::vector<Virus *>::iterator ImmuneSystem :: getVirusListIteratorEnd() { return (*virus_list_).end(); }
/* 待機ウイルスセット */
Virus *ImmuneSystem :: getStandByVirusAt( int n ) const { return (*stand_by_virus_list_).at(n); }
void ImmuneSystem :: pushStandByVirus( Virus *v ) { (*stand_by_virus_list_).push_back( v ); }
int ImmuneSystem :: getStandByVirusListSize() const { return (*stand_by_virus_list_).size(); }
bool ImmuneSystem :: hasNoStandByVirus() const { return (*stand_by_virus_list_).empty(); }
std::vector<Virus *>::iterator ImmuneSystem :: getStandByVirusListIteratorBegin() { return (*stand_by_virus_list_).begin(); }
std::vector<Virus *>::iterator ImmuneSystem :: getStandByVirusListIteratorEnd() { return (*stand_by_virus_list_).end(); }
void ImmuneSystem :: eraseStandByVirus( std::vector<Virus *>::iterator it ) { (*stand_by_virus_list_).erase( it ); }
void ImmuneSystem :: clearStandByVirus() { (*stand_by_virus_list_).clear(); }

int ImmuneSystem :: getOnSetVirusListSize() {
  int ret = 0;
  C_ITERATOR(Virus *) it_v = getVirusListIteratorBegin();            /* ウイルスリストの先頭から */
  while( it_v != getVirusListIteratorEnd() ) {                       /* 末尾まで */
    if( (*it_v)->getInfectionTime() > V_INCUBATION_PERIOD ) {
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
    if( num == n and (*it_v)->getInfectionTime() > V_INCUBATION_PERIOD ) {
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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: infection( Tag & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool ImmuneSystem :: infection( Agent &self, Virus &v )
{
  return immunesystem_strategy_->infection(self, v);
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
  return immunesystem_strategy_->response(self);
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  TagFlip :: response
 * Description:  タグを１つずつフリップする
 *               感染期間を返す
 *--------------------------------------------------------------------------------------
 */
int TagFlip :: response(Agent &self)
{
  if( self.getImmuneSystem()->hasNoVirus() ) {                       /* 感染していなければ */
    self.getImmuneSystem()->resetInfectionTime();                    /* 感染期間は０で */
    return 0;                                                        /* 終了する */
  }

  ITERATOR(Virus *) it
    = self.getImmuneSystem()->getVirusListIteratorBegin();           /* 先頭のウイルスに対し */

  flip_once(                                                         /* ひとつフリップする */
      self.getTag()->getTag()+(*it)->getClingPoint(),
      (*it)->getTag()->getTag(),
      (*it)->getLen() );

  if( self.hasImmunity( **it ) )                                     /* そのウイルスに対して */
  {                                                                  /* 免疫獲得すれば */
    // XXX: 要検討
    self.getImmuneSystem()->eraseVirus( it );                        /* 保持ウイルスから v(先頭) を削除 */
  }

  ITERATOR( Virus * ) it_v                                           /* 先頭のウイルスデータから */
    = self.getImmuneSystem()->getVirusListIteratorBegin();
  while( it_v != self.getImmuneSystem()->getVirusListIteratorEnd() ) /* 末尾まで */
  {
    (*it_v)->incrementInfectionTime();                               /* 感染期間を */
    it_v++;                                                          /* 増やす */
  }

  if( self.getImmuneSystem()->getVirusListSize() > 0 ) {             /* まだ感染していれば */
    self.getImmuneSystem()->incrementInfectionTime();                /* 総感染期間を増やして */
  } else {                                                           /* そうでなければ */
    self.getImmuneSystem()->resetInfectionTime();                    /* 感染期間を０にリセット */
  }
  return self.getImmuneSystem()->getInfectionTime();                 /* 総染期間を返す */
}
void ImmuneSystem :: incrementInfectionTime() {
  /*-----------------------------------------------------------------------------
   *  感染期間を増やす
   *-----------------------------------------------------------------------------*/
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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  TagFlip :: infection
 * Description:  感染したら true を返す
 *--------------------------------------------------------------------------------------
 */
bool TagFlip :: infection( Agent &self, Virus &v )
{
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
  new_v->setClingPoint( new_v->searchStartPoint( *self.getTag() ) );
  // XXX: ウイルスの関数にする setClingPoint( Tag * );
  self.getImmuneSystem()->pushVirus( new_v );                        /* 保持ウイルスリストに追加する */

//  Monitor::Instance().countUpInfectionContact(vdata->v_);          /* 感染のために接触した回数を増やす */
  return true;                                                       /* 感染して true を返す */
}
