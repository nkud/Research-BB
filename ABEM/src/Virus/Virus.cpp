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
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus()
 * Description:  ウイルスをデフォルトの長さで初期化
 *               タグもランダム
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus() :
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( V_DEFAULT_LEN );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}

Virus :: Virus( __SearchStrategy *sp ) :
  search_strategy_( sp ),
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( V_DEFAULT_LEN );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
  sp->check( V_DEFAULT_LEN );
}

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
double Virus :: getRate() const { return rate_; }
void Virus :: setRate( const double r ) { rate_ = r; }

/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( int )
 * Description:  ウイルスの長さを指定して初期化
 *               タグはランダム
 *----------------------------------------------------------------------------------- */
Virus :: Virus( int l, double r ):
  rate_( r )                                                         /* 感染確率を指定 */
{
  tag_ = new Tag( l );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( const char * )
 * Description:  ウイルスのタグを指定して初期化
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus( const char *str ) :
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( str );
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
 *      Method:  Normal :: searchStartPoint( const Tag &, const Tag & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Normal :: searchStartPoint( const Virus &myself, const Tag &tag ) const {
  int sp = -1;                                                       /* 取り付く位置 */
  sp                                                                 /* 取り付く位置を計算する */
    = min_ham_distance_point( tag.getTag(), myself.getTag()->getTag(), tag.getLen(), myself.getTag()->getLen() );
  return sp;                                                         /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Normal :: getSearchType() const {
  return __NORMAL__;                                                 /* 通常ウイルスであることを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Fixed :: searchStartPoint( const Tag &, const Tag & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Fixed :: searchStartPoint( const Virus &myself, const Tag &tag ) const {
  return sp_;                                                        /* 取り付く位置を返す */
}


/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus
 * Description:  
 *----------------------------------------------------------------------------------- */
Virus :: Virus( int l, __SearchStrategy *sp ):
  search_strategy_( sp ),                                            /* 戦略指定 */
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
  rate_( INFECTION_RATE )                                            /* 感染確率は初期設定 */
{
  tag_ = new Tag( str );
  tag_->setTagRandom();                                              /* タグをランダムに初期化 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Fixed :: getSearchType() const {
  return __FIXED__;                                                  /* 固定ウイルスであることを返す */
}

void Normal :: check ( int vlen ) const {
  return;
}

void Fixed :: check( int vlen ) const {
  assert( vlen+sp_ <= A_DEFAULT_LEN );
}
