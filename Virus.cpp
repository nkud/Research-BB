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
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus() :
    __TagInterface(TAG_LEN_V)
{
    log("init with default");
    FOR( i, TAG_LEN_V ) {
        tag_[i] = rand_binary();
    }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Virus :: Virus( int )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Virus :: Virus( const char *tag ) :
    __TagInterface( strlen(tag) )
{
    log("init with char");
    int len = strlen(tag);
    log(len);
    log(tag);
    FOR( i, len ) {
        tag_[i] = tag[i] - '0';
    }
}
