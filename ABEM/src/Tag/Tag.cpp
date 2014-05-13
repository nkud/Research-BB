/*
 * =====================================================================================
 *
 *       Filename:  Tag.cpp
 *
 *    Description:  タグのインターフェイス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Tag.h"
#include "Global.h"
#include "Function.h"

#include <cstring>
#include <cassert>


Tag :: Tag( int n, tag_t *t )
{
  len_ = n;
  tag_ = new tag_t[ n ];
  FOR( i, n )
  {
    tag_[i] = t[i];                                                 /* すべてを０で初期化 */
  }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: setTagRandom()
 * Description:  タグをランダムに初期化する
 *--------------------------------------------------------------------------------------
 */
void Tag :: setTagRandom() {
    assert( len_ > 0 );
    FOR( i, len_ )
    {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化  */
    }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: Tag( int )
 * Description:  長さを指定して初期化する
 *--------------------------------------------------------------------------------------
 */
Tag :: Tag( int l ) :
    len_( l ),                                                       /* 指定された長さで初期化 */
    tag_( 0 )
{
    tag_ = new tag_t[ l ];                                           /* タグのメモリ領域を確保 */
    FOR( i, l )
    {
        tag_[i] = 0;                                                 /* すべてを０で初期化 */
    }
}
Tag :: ~Tag() {                                /* デストラクタ */
    delete[] tag_;                                                   /* タグのメモリ領域を削除 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: changeTagLenTo( int )
 * Description:  タグの長さを変更する
 *               変更後はすべて０で初期化
 *--------------------------------------------------------------------------------------
 */
void Tag :: changeTagLenTo( int n ) {
    len_ = n;                                                        /* 長さを再設定 */
    delete[] tag_;                                                   /* 既存をメモリ削除 */
    tag_ = new tag_t[n];                                             /* 新たにメモリ割当 */
    FOR( i, n )
    {
        tag_[i] = 0;                                                 /* すべてを０で初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: Tag( const char * )
 * Description:  タグを文字列で直接指定して初期化
 *--------------------------------------------------------------------------------------
 */
Tag :: Tag( const char *str ) :
    len_( strlen( str ) ),                                           /* 文字列の長さで初期化 */
    tag_( 0 )
{
    assert( len_ > 0 );                                              /* 文字列の長さが０以下ならエラー */
    tag_ = new tag_t[ len_ ];                                        /* タグのメモリ領域を確保 */

    FOR( i, len_ ) {
        tag_[ i ] = str[ i ] - '0';                                  /* 指定された文字列で初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: getTag_()
 * Description:  タグを返す
 *--------------------------------------------------------------------------------------
 */
tag_t *Tag :: getTag() const
{
    return tag_;                                                     /* タグを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Tag :: getTagLen()
 * Description:  タグの長さを返す
 *----------------------------------------------------------------------------------- */
int Tag :: getLen() const {
    return len_;                                                     /* タグの長さを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Tag :: tagAt( int )
 * Description:  指定した位置のタグの値を返す
 *----------------------------------------------------------------------------------- */
tag_t Tag :: tagAt( const int n ) const {
    assert( n < len_ );                                              /* 指定した位置が全長を越えるとエラー */
    return tag_[n];                                                  /* 指定された位置のタグを返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: printTag()
 * Description:  タグを表示する
 *--------------------------------------------------------------------------------------
 */
void Tag :: printTag() const {
    std::cout << "[ " <<this<< " ]" << ": ";                         /* 自身のポインタを表示する */
    FOR( i, len_ ) {
        std::cout << tag_[i];                                        /* タグを表示する */
    }
    std::cout << std::endl;                                          /* 改行 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Tag :: setTag( tag_t *, int l )
 * Description:  タグを設定する
 *--------------------------------------------------------------------------------------
 */
void Tag :: setTag( const tag_t *t, int l ) {
    assert( l > 0 );                                                 /* 全長が０以下ならエラー */
    changeTagLenTo( l );                                             /* 全長を変更する */
    while( l-- ) {
        tag_[l] = t[l];                                              /* タグをコピーしていく */
    }
}
