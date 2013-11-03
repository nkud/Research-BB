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
    len_(l),
    tag_(0)
{
    tag_ = new tag_t[ l ];                      /* タグを初期化 */
    FOR( i, l )
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
int *__TagInterface :: getTag_()
{
    return tag_;
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
