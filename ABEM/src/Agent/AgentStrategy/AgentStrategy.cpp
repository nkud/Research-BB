/*
 * =====================================================================================
 *
 *       Filename:  AgentStrategy.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Agent.h"
#include "AgentStrategy.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Relocate :: move( int &, int & )
 * Description:  再配置による戦略
 *--------------------------------------------------------------------------------------
 */
void Relocate :: move( int &x, int &y ) {
  x = rand_interval_int( 0, WIDTH-1 );
  y = rand_interval_int( 0, WIDTH-1 );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  RandomWalk :: move( int &, int & )
 * Description:  ランダムウォークによる戦略
 *--------------------------------------------------------------------------------------
 */
void RandomWalk :: move( int &x, int &y ) {
  x += rand_interval_int( -distance_, distance_ );
  y += rand_interval_int( -distance_, distance_ );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  CoupleTag :: childbirth
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent* CoupleTag :: childbirth( const Agent &a, const Agent &b ) const {
  assert( isOppositeSex( a, b ) );                                   /* 同性ならエラー */

  Agent *child = new Agent(
      a.getMovingStrategy(),
      a.getChildBirthStrategy(),
      a.getLen(),
      b.getLen()
      );                                                             /* 子供を作成 */

  child->resetParam();                                               /* パラメータをリセット */

  tag_t *couple_tag = new tag_t[ a.getLen() + b.getLen() ];          /* 両親を元にした */
  tag_t *p = couple_tag;                                             /* カップルタグを作成 */

  FOR( i, a.getLen() ) {                                             /* 両親の */
    *(p++) = a.tagAt( i );                                           /* タグを */
  }
  FOR( i, b.getLen() ) {                                             /* コピーしていく */
    *(p++) = b.tagAt( i );
  }
  child->setTag(                                                     /* カップルタグを元に */
      couple_tag+rand_interval_int(0,a.getLen()) , a.getLen()        /* XXX:子供のタグを作成 */
      );
  delete[] couple_tag;                                               /* カップルタグを削除 */

  if( a.getSex() == __FEMALE__ ) {                                   /* 母親の居場所に */
    int tx = a.getX();
    int ty = a.getY();
    child->setX( tx );                                               /* 子供を配置 */
    child->setY( ty );
  } else {
    int tx = b.getX();
    int ty = b.getY();
    child->setX( tx );
    child->setY( ty );
  }

  return child;                                                      /* 子供を返す */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  InheritanceLen :: childbirth
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent* InheritanceLen :: childbirth( const Agent &a, const Agent &b ) const {
  assert( isOppositeSex( a, b ) );                                   /* 同性ならエラー */

  Agent *child = new Agent(
      a.getMovingStrategy(),
      a.getChildBirthStrategy(),
      a.getLen(),
      b.getLen()
      );                                                             /* 子供を作成 */

  child->resetParam();                                               /* パラメータをリセット */

  if( a.getSex() == __FEMALE__ ) {                                   /* 母親の居場所に */
    int tx = a.getX();
    int ty = a.getY();
    child->setX( tx );                                               /* 子供を配置 */
    child->setY( ty );
  } else {
    int tx = b.getX();
    int ty = b.getY();
    child->setX( tx );
    child->setY( ty );
  }

  return child;                                                      /* 子供を返す */
}

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
  flip_once( self.getTag()+(*it)->sp_, (*it)->v_->getTag(), (*it)->v_->getLen() );            /* ひとつフリップする */

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
    = new VirusData( v, v.searchStartPoint( self ) );
  self.pushVirusData( vdata );                                       /* 保持ウイルスリストに追加する */

//  Monitor::Instance().countUpInfectionContact(vdata->v_);            /* 感染のために接触した回数を増やす */
  return true;                                                       /* 感染して true を返す */
}
