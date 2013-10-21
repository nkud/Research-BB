#include "Virus.h"
#include "Function.h"

Virus :: Virus( int len ) :
    __TagInterface( len )
{
    log("init virus");
    FOR( i, len_ )
    {
        tag_[i] = rand_binary();
    }
}
