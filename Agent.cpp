#include "Agent.h"
#include "Virus.h"
#include "Function.h"

Agent :: Agent( int len ) :
    __TagInterface( len )
{
    log("init agent");
    FOR( i, len_ )
    {
        tag_[ i ] = rand_binary();
    }
}

bool Agent :: hasImmunity( Virus &v )           /* true -> 免疫獲得済み */
{
    if( min_ham_distance( tag_, v.tag_, len_, v.len_ ) > 0 )
        return false;                           /* 最小ハミング距離が１以上なら */
    else
        return true;
}
