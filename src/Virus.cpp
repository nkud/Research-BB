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
    __TagInterface( TAG_LEN_V ),                                     /* タグの長さは初期設定 */
    rate_( INFECTION_RATE )                                          /* 感染確率は初期設定 */
{
    FOR( i, TAG_LEN_V ) {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化 */
    }
}

Virus :: Virus( __SearchStrategy *sp ) :
    __TagInterface( TAG_LEN_V ),                                     /* タグの長さは初期設定 */
    search_strategy_( sp ),
    rate_( INFECTION_RATE )                                          /* 感染確率は初期設定 */
{
    FOR( i, TAG_LEN_V ) {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化 */
    }
    sp->check( TAG_LEN_V );
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
    __TagInterface( l ),                                             /* 長さを指定 */
    rate_( r )                                                       /* 感染確率を指定 */
{
    FOR( i, l ) {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( const char * )
 * Description:  ウイルスのタグを指定して初期化
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus( const char *str ) :
    __TagInterface( str ),                                           /* タグを直接指定 */
    rate_( INFECTION_RATE )                                          /* 感染確率は初期設定 */
{}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: searchStartPoint( __TagInterface & )
 * Description:  タグに対して、ハミング距離が最小となる位置に取り付く
 *--------------------------------------------------------------------------------------
 */
int Virus :: searchStartPoint( const __TagInterface &tag ) const {
    return search_strategy_->searchStartPoint( *this, tag );          /* 取り付く位置を返す */
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: getSearchType() const
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Virus :: getSearchType() const {
    return search_strategy_->getSearchType();                         /* 戦略の種類を返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Normal :: searchStartPoint( const __TagInterface &, const __TagInterface & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Normal :: searchStartPoint( const __TagInterface &myself, const __TagInterface &tag ) const {
    int sp = -1;                                                     /* 取り付く位置 */
    sp                                                               /* 取り付く位置を計算する */
        = min_ham_distance_point( tag.getTag(), myself.getTag(), tag.getLen(), myself.getLen() );
    return sp;                                                       /* 取り付く位置を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Normal :: getSearchType() const {
    return __NORMAL__;                                               /* 通常ウイルスであることを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Fixed :: searchStartPoint( const __TagInterface &, const __TagInterface & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int Fixed :: searchStartPoint( const __TagInterface &myself, const __TagInterface &tag ) const {
    return sp_;                                                       /* 取り付く位置を返す */
}


/*--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus
 * Description:  
 *----------------------------------------------------------------------------------- */
Virus :: Virus( int l, __SearchStrategy *sp ):
    __TagInterface( l ),                                             /* 長さを指定 */
    search_strategy_( sp ),                                           /* 戦略指定 */
    rate_( INFECTION_RATE )                                          /* 感染確率を指定 */
{
    FOR( i, l ) {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化 */
    }
    sp->check( l );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( const char *, __SearchStrategy * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus( const char *str, __SearchStrategy *sp ) :
    __TagInterface( str ),                                           /* タグを直接指定 */
    search_strategy_( sp ),                                           /* 戦略指定 */
    rate_( INFECTION_RATE )                                          /* 感染確率は初期設定 */
{ }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Normal :: getSearchType()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__SEARCH__TYPE__ Fixed :: getSearchType() const {
    return __FIXED__;                                                /* 固定ウイルスであることを返す */
}

void Normal :: check ( int vlen ) const {
    return;
}

void Fixed :: check( int vlen ) const {
    assert( vlen+sp_ <= TAG_LEN_A );
}
