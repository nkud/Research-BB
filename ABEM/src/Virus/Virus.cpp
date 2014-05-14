/*
 * =====================================================================================
 *
 *       Filename:  Virus.cpp
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstring>

#include "Global.h"
#include "Virus.h"
#include "VirusStrategy.h"
#include "Function.h"
#include "Tag.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus()
 * Description:  ウイルスをデフォルトの長さで初期化
 *               タグもランダム
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus() :
  cling_point_( 0 ),
  infection_time_( 0 ),
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( V_DEFAULT_LEN );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}

Virus :: Virus( __SearchStrategy *sp ) :
  search_strategy_( sp ),
  cling_point_( 0 ),
  infection_time_( 0 ),
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( V_DEFAULT_LEN );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
  sp->check( V_DEFAULT_LEN );
}
Virus :: Virus( int l, double r ):
  rate_( r )                                                         /* 感染確率を指定 */
{
  tag_ = new Tag( l );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}

Virus :: Virus( const char *str ) :
  cling_point_( 0 ),
  infection_time_( 0 ),
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( str );
}

Virus :: Virus( Virus *v ) {
  cling_point_ = 0;
  infection_time_ = 0;
  rate_ = v->getRate();
  tag_ = new Tag( v->getLen(), v->getTag()->getTag() );
  search_strategy_ = new Normal();
}

Virus :: ~Virus() {
  delete tag_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
double Virus :: getRate() const { return rate_; }
void Virus :: setRate( const double r ) { rate_ = r; }

bool Virus :: isEqualTo( Virus &v ) {
  /*-----------------------------------------------------------------------------
   *  ウイルス v にタグが等しければ true を返す
   *-----------------------------------------------------------------------------*/
  int len = getLen();
  if( len != v.getLen() ) {
    return false;
  }
  FOR( i, len ) {
    if( tagAt(i) != v.tagAt(i) ) {
      return false;
    }
  }
  return true;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: searchStartPoint( Tag & )
 * Description:  タグに対して、ハミング距離が最小となる位置に取り付く
 *--------------------------------------------------------------------------------------
 */
int Virus :: searchStartPoint( const Tag &tag ) const {
  return search_strategy_->searchStartPoint( *this, tag );           /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: getSearchType() const
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Virus :: getSearchType() const {
  return search_strategy_->getSearchType();                          /* 戦略の種類を返す */
}
/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus
 * Description:  
 *----------------------------------------------------------------------------------- */
Virus :: Virus( int l, __SearchStrategy *sp ):
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 ),
  rate_( INFECTION_RATE )                                            /* 感染確率を指定 */
{
  tag_ = new Tag( l );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */

  sp->check( l );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( const char *, __SearchStrategy * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus( const char *str, __SearchStrategy *sp ) :
  search_strategy_( sp ),                                            /* 戦略指定 */
  cling_point_( 0 ),
  infection_time_( 0 ),
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( str );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}
