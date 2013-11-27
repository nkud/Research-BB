/*
 * =====================================================================================
 *
 *       Filename:  TagInterface.cpp
 *
 *    Description:  タグのインターフェイス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "TagInterface.h"
#include "Global.h"

#include <cstring>
#include <cassert>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: __TagInterface( int )
 * Description:  長さを指定して初期化する
 *--------------------------------------------------------------------------------------
 */
__TagInterface :: __TagInterface( int l ) :
    len_( l ),
    tag_( 0 )
{
    tag_ = new tag_t[ l ];                                           /* タグを初期化 */
    FOR( i, l )
    {
        tag_[i] = 0;                                                 /* すべてを０で初期化 */
    }
}
__TagInterface :: ~__TagInterface() {                                /* デストラクタ */
    delete[] tag_;                                                   /* タグのメモリ領域を削除 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: changeTagLenTo( int )
 * Description:  タグの長さを変更する
 *               変更後はすべて０で初期化
 *--------------------------------------------------------------------------------------
 */
void __TagInterface :: changeTagLenTo( int n ) {
    len_ = n;                                                        /* 長さを設定 */
    delete[] tag_;                                                   /* 既存をメモリ削除 */
    tag_ = new tag_t[n];                                             /* 新たにメモリ割当 */
    FOR( i, n )
    {
        tag_[i] = 0;                                                 /* すべてを０で初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: __TagInterface( const char * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__TagInterface :: __TagInterface( const char *str ) :
    len_( strlen( str ) ),
    tag_( 0 )
{
    tag_ = new tag_t[ len_ ];

    FOR( i, len_ ) {
        tag_[ i ] = str[ i ] - '0';
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: getTag_()
 * Description:  タグを返す
 *--------------------------------------------------------------------------------------
 */
tag_t *__TagInterface :: getTag() const
{
    return tag_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: getTagLen()
 * Description:  タグの長さを返す
 *----------------------------------------------------------------------------------- */
int __TagInterface :: getLen() const {
    return len_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: tagAt( int )
 * Description:  指定した位置のタグの値を返す
 *----------------------------------------------------------------------------------- */
tag_t __TagInterface :: tagAt( const int n ) const {
    assert( n < len_ );                                              /* 指定した位置が全長を越えるとエラー */
    return tag_[n];
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: printTag()
 * Description:  タグを表示する
 *--------------------------------------------------------------------------------------
 */
void __TagInterface :: printTag() {
    std::cout << "[ " <<this<< " ]" << ": ";
    FOR( i, len_ ) {
        std::cout << tag_[i];
    }
    std::cout << std::endl;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: setTag( tag_t *, int l )
 * Description:  タグを設定する
 *--------------------------------------------------------------------------------------
 */
void __TagInterface :: setTag( const tag_t *t, int l ) {
    assert( l > 0 );                                                 /* 全長が０以下ならエラー */
    changeTagLenTo( l );                                             /* 全長を変更する */
    while( l-- ) {
        tag_[l] = t[l];                                              /* タグをコピーしていく */
    }
}
