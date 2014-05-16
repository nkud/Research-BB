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


/*-----------------------------------------------------------------------------
 *
 *  コンストラクタ
 *
 *-----------------------------------------------------------------------------*/
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


/*-----------------------------------------------------------------------------
 *  Virus :: Virus( Virus * )
 *      ウイルスをコピーするコンストラクタ
 *-----------------------------------------------------------------------------*/
Virus :: Virus( Virus *v ) {
  cling_point_ = 0;
  infection_time_ = 0;
  rate_ = v->getRate();
//  tag_ = new Tag( v->getLen(), v->getTag()->getTag() );
  tag_ = new Tag( v->getTag() );
  search_strategy_ = new Normal();

  tag_->mutation( V_MUTATION_RATE );
}

/*-----------------------------------------------------------------------------
 *  Virus :: ~Virus()
 *-----------------------------------------------------------------------------*/
Virus :: ~Virus() {
  delete tag_;
  delete search_strategy_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
double Virus :: getRate() const { return rate_; }
void Virus :: setRate( const double r ) { rate_ = r; }

/*-----------------------------------------------------------------------------
 *  Virus :: isEqualTo( Virus & )
 *      ウイルスのタグに等しければ true を返す
 *-----------------------------------------------------------------------------*/
bool Virus :: isEqualTo( Virus &v ) {
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

/*-----------------------------------------------------------------------------
 *  Virus :: mutation()
 *      突然変異を起こす
 *-----------------------------------------------------------------------------*/
void Virus :: mutation() {
  getTag()->mutation();
}
void Virus :: mutation( double prob ) {
  if ( probability( prob ) ) {
    getTag()->mutation( prob );
  }
}
