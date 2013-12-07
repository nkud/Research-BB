/*
 * =====================================================================================
 *
 *       Filename:  Virus.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include <cstdlib>
#include <cstring>

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
    __TagInterface( TAG_LEN_V ),
    rate_( INFECTION_RATE )
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
    __TagInterface( l ),
    rate_( r )
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
    __TagInterface( str )
{}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: searchStartPoint( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Virus :: searchStartPoint( __TagInterface &tag ) {
    int sp = -1;
    sp = min_ham_distance_point( tag.getTag(), getTag(), tag.getLen(), getLen() );
    return sp;
}
