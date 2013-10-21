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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  __TagInterface :: __TagInterface( int )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
__TagInterface :: __TagInterface( int n )
{
    len_ = n;
    tag_ = new tag_t[ n ];                      /* タグを初期化 */
    FOR( i, n )
    {
        tag_[i] = 0;                            /* すべてを０で初期化 */
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
 *      Method:  __TagInterface :: hamDistanceWith( tag_t * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
//int __TagInterface :: hamDistanceWith( tag_t *t )
//{
//    return ham
//}
