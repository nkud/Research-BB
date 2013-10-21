#include "Virus.h"
#include "Function.h"

Virus :: Virus() :
    __TagInterface(TAG_LEN_V)
{
    FOR( i, TAG_LEN_V )
    {
        tag_[i] = rand_binary();
    }
}
