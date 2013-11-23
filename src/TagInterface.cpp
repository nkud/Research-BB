/*
 * =====================================================================================
 *
 *       Filename:  TagInterface.cpp
 *
 *    Description:  
 *
 *         Author:  
 *   Organization:  
 *
 * =====================================================================================
 */

#include "TagInterface.h"
#include "Global.h"

#include <cstring>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: __TagInterface( int )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__TagInterface :: __TagInterface( int l ) :
    len_( l ),
    tag_( 0 )
{
    tag_ = new tag_t[ l ];                      /* タグを初期化 */
    FOR( i, l )
    {
        tag_[i] = 0;                            /* すべてを０で初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: changeTagLenTo()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void __TagInterface :: changeTagLenTo( int n ) { /* XXX: OK ? */
    len_ = n;
    delete[] tag_;                              /* 既存をメモリ削除 */
    tag_ = new tag_t[n];                        /* 新たにメモリ割当 */
    FOR( i, n )
    {
        tag_[i] = 0;                            /* すべてを０で初期化 */
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
 * Description:  
 *--------------------------------------------------------------------------------------
 */
tag_t *__TagInterface :: getTag() const
{
    return tag_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: getTagLen()
 * Description:  
 *----------------------------------------------------------------------------------- */
int __TagInterface :: getLen() const {
    return len_;
}

/*--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: tagAt( int )
 * Description:  
 *----------------------------------------------------------------------------------- */
tag_t __TagInterface :: tagAt( const int n ) const {
    if( n >= len_ ) return -1;                   /* ERROR */
    return tag_[ n ];
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: printTag()
 * Description:  
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
 *      Method:  __TagInterface :: setTag( tag_t * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void __TagInterface :: setTag( tag_t *t, int l ) {
    changeTagLenTo( l );
    tag_ = t;
}
