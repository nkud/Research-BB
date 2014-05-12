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
#include "AgentStrategy.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  TagFlip :: response
 * Description:  タグを１つずつフリップする
 *--------------------------------------------------------------------------------------
 */
void TagFlip :: response(Agent &self)
{
  if( self.hasNoVirusData() ) return;                                /* 保持ウイルスなし、終了する */

  ITERATOR(VirusData *) it = self.getVirusListIteratorBegin();       /* 先頭のウイルスに対し */
  flip_once( self.getTag()->getTag()+(*it)->sp_, (*it)->v_->getTag()->getTag(), (*it)->v_->getLen() );            /* ひとつフリップする */

  if( self.hasImmunity( *((*it)->v_) ) )
  {                                                                  /* 免疫獲得すれば */
    // XXX: 要検討
    self.eraseVirusData( it );                                       /* 保持ウイルスから v(先頭) を削除して */
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  TagFlip :: infection
 * Description:  感染したら true を返す
 *--------------------------------------------------------------------------------------
 */
bool TagFlip :: infection(Agent &self, Virus &v)
{
  if( self.getVirusListSize() >= A_MAX_V_CAN_HAVE ) {                /* 最大値を越えてたら */
    return false;                                                    /* 感染せずに終了 */
  }
  ITERATOR(VirusData *) it_vd = self.getVirusListIteratorBegin();    /* 保持ウイルスリストを取得 */
  while( it_vd != self.getVirusListIteratorEnd() ) {                 /* 既に保持しているウイルスなら */
    if( (*it_vd)->v_ == &v ) {
      return false;                                                  /* 感染せずに終了 */
    }
    it_vd++;                                                         /* 次の保持ウイルス */
  }
  if( self.hasImmunity( v ) ) {                                      /* 免疫獲得済みなら  */
    return false;                                                    /* 感染せずに終了 */
  }
  VirusData *vdata                                                   /* 新しいウイルスデータを作成して */
    //        = new VirusData( v, min_ham_distance_point( tag_, v.getTag(), len_, v.getLen() ) );
    = new VirusData( v, v.searchStartPoint( *self.getTag() ) );
  self.pushVirusData( vdata );                                       /* 保持ウイルスリストに追加する */

//  Monitor::Instance().countUpInfectionContact(vdata->v_);            /* 感染のために接触した回数を増やす */
  return true;                                                       /* 感染して true を返す */
}
