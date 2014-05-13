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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: ImmuneSystem
 * Description:  コンストラクタ
 *--------------------------------------------------------------------------------------
 */
ImmuneSystem :: ImmuneSystem() :
  infection_time_( 0 )
{
  vlist_ = new std::vector<VirusData *>;
  stand_by_list_ = new std::vector<Virus *>;
  immunesystem_strategy_ = new TagFlip();
}
ImmuneSystem :: ~ImmuneSystem() {
  delete vlist_;
  delete stand_by_list_;
  delete immunesystem_strategy_;
}
/*-----------------------------------------------------------------------------
 *
 *  ウイルス操作セット
 *
 *-----------------------------------------------------------------------------*/
/* 保持ウイルスセット */
VirusData *ImmuneSystem :: getVirusDataAt( int n ) const { return (*vlist_).at( n ); }
int ImmuneSystem :: getVirusListSize() const { return (*vlist_).size(); }
void ImmuneSystem :: pushVirusData( VirusData *vd ) { (*vlist_).push_back( vd ); }
void ImmuneSystem :: eraseVirusData( std::vector<VirusData *>::iterator it ) { delete (*it); (*vlist_).erase( it ); }
bool ImmuneSystem :: hasNoVirusData() const { if( (*vlist_).empty() ) return true; else return false; }
std::vector<VirusData *>::iterator ImmuneSystem :: getVirusListIteratorBegin() { return (*vlist_).begin(); }
std::vector<VirusData *>::iterator ImmuneSystem :: getVirusListIteratorEnd() { return (*vlist_).end(); }
/* 待機ウイルスセット */
Virus *ImmuneSystem :: getStandByVirusAt( int n ) const { return (*stand_by_list_).at(n); }
void ImmuneSystem :: pushStandByVirus( Virus *v ) { (*stand_by_list_).push_back( v ); }
int ImmuneSystem :: getStandByListSize() const { return (*stand_by_list_).size(); }
bool ImmuneSystem :: hasNoStandByVirus() const { return (*stand_by_list_).empty(); }
std::vector<Virus *>::iterator ImmuneSystem :: getStandByListIteratorBegin() { return (*stand_by_list_).begin(); }
std::vector<Virus *>::iterator ImmuneSystem :: getStandByListIteratorEnd() { return (*stand_by_list_).end(); }
void ImmuneSystem :: eraseStandByVirus( std::vector<Virus *>::iterator it ) { (*stand_by_list_).erase( it ); }
void ImmuneSystem :: clearStandByVirus() { (*stand_by_list_).clear(); }

int ImmuneSystem :: getOnSetVirusListSize() const {
  int ret = 0;
  C_ITERATOR(VirusData *) it_vd = (*vlist_).begin();                 /* ウイルスリストの先頭から */
  while( it_vd != (*vlist_).end() ) {                                /* 末尾まで */
    if( (*it_vd)->infection_time_ > V_INCUBATION_PERIOD ) {
      ret++;
    }
    it_vd++;                                                         /* 次のウイルスリストへ */
  }
  return ret;
}
VirusData *ImmuneSystem :: getOnSetVirusDataAt( int n ) const {
  int num = 0;
  C_ITERATOR(VirusData *) it_vd = (*vlist_).begin();                 /* ウイルスリストの先頭から */
  while( it_vd != (*vlist_).end() ) {                                /* 末尾まで */
    if( num == n and (*it_vd)->infection_time_ > V_INCUBATION_PERIOD ) {
      return (*it_vd);
    }
    it_vd++;                                                         /* 次のウイルスリストへ */
    num++;
  }
  return (*it_vd);
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  ImmuneSystem :: hasVirus( Virus & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
bool ImmuneSystem :: hasVirus( Virus &v ) const {
  C_ITERATOR(VirusData *) it_vd = (*vlist_).begin();                 /* ウイルスリストの先頭から */
  while( it_vd != (*vlist_).end() ) {                                /* 末尾まで */
    if( (*it_vd)->v_ == &v ) {                                       /* 感染済みであれば */
      return true;                                                   /* true を返す */
    }
    it_vd++;                                                         /* 次のウイルスリストへ */
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
  if( self.getImmuneSystem()->hasNoVirusData() ) {                   /* 感染していなければ */
    self.getImmuneSystem()->resetInfectionTime();                    /* 感染期間は０で */
    return 0;                                                        /* 終了する */
  }

  ITERATOR(VirusData *) it
    = self.getImmuneSystem()->getVirusListIteratorBegin();           /* 先頭のウイルスに対し */

  flip_once(                                                         /* ひとつフリップする */
      self.getTag()->getTag()+(*it)->sp_,
      (*it)->v_->getTag()->getTag(),
      (*it)->v_->getLen() );

  if( self.hasImmunity( *((*it)->v_) ) )                             /* そのウイルスに対して */
  {                                                                  /* 免疫獲得すれば */
    // XXX: 要検討
    self.getImmuneSystem()->eraseVirusData( it );                    /* 保持ウイルスから v(先頭) を削除 */
  }

  ITERATOR( VirusData * ) it_vd                                      /* 先頭のウイルスデータから */
    = self.getImmuneSystem()->getVirusListIteratorBegin();
  while( it_vd != self.getImmuneSystem()->getVirusListIteratorEnd() ) /* 末尾まで */
  {
    (*it_vd)->infection_time_++;                                     /* 感染期間を */
    it_vd++;                                                         /* 増やす */
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
bool TagFlip :: infection(Agent &self, Virus &v)
{
  if( self.getImmuneSystem()->getVirusListSize() >= A_MAX_V_CAN_HAVE ) {                /* 最大値を越えてたら */
    return false;                                                    /* 感染せずに終了 */
  }
  ITERATOR(VirusData *) it_vd = self.getImmuneSystem()->getVirusListIteratorBegin();    /* 保持ウイルスリストを取得 */
  while( it_vd != self.getImmuneSystem()->getVirusListIteratorEnd() ) {                 /* 既に保持しているウイルスなら */
    if( (*it_vd)->v_ == &v ) {
      return false;                                                  /* 感染せずに終了 */
    }
    it_vd++;                                                         /* 次の保持ウイルス */
  }
  if( self.hasImmunity( v ) ) {                                      /* 免疫獲得済みなら  */
    return false;                                                    /* 感染せずに終了 */
  }
  VirusData *vdata                                                   /* 新しいウイルスデータを作成して */
    = new VirusData( v, v.searchStartPoint( *self.getTag() ), 0 );
  self.getImmuneSystem()->pushVirusData( vdata );                                       /* 保持ウイルスリストに追加する */

//  Monitor::Instance().countUpInfectionContact(vdata->v_);            /* 感染のために接触した回数を増やす */
  return true;                                                       /* 感染して true を返す */
}
