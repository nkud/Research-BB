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
#include <stdlib.h>

#include "Virus.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus() :
    __TagInterface(TAG_LEN_V)
{
    FOR( i, TAG_LEN_V )
    {
        tag_[i] = rand_binary();
    }
}
