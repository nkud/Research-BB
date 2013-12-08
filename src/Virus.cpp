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
    int sp = -1;                                                     /* 取り付く位置 */
    sp                                                               /* 取り付く位置を計算する */
        = min_ham_distance_point( tag.getTag(), getTag(), tag.getLen(), getLen() );
    return sp;                                                       /* 取り付く位置を返す */
}


/*--------------------------------------------------------------------------------------
 *      Method:  FixedVirus :: FixedVirus
 * Description:  
 *----------------------------------------------------------------------------------- */
FixedVirus :: FixedVirus( int l, double r, int fsp ):
    Virus( l, r ),                                                   /* タグ長、感染確率を指定 */
    fixed_start_point_( fsp )                                        /* 取り付く位置を指定（最左が０） */
{
    assert( l+fsp <= TAG_LEN_A );                                               /* 取り付く位置がはみ出てたらエラー */
    FOR( i, l ) {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化 */
    }
}

/*--------------------------------------------------------------------------------------
 *      Method:  FixedVirus :: searchStartPoint( const __TagInterface & )
 * Description:  
 *----------------------------------------------------------------------------------- */
int FixedVirus :: searchStartPoint( const __TagInterface &tag ) const {
    LOG(fixed_start_point_);
    return fixed_start_point_;                                                       /* 取り付く位置を返す */
}
