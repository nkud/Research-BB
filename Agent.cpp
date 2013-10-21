#include "Agent.h"
#include "Virus.h"
#include "Function.h"

Agent :: Agent( int len ) :
    __TagInterface( len )
{
    log("init agent");
}

bool Agent :: hasImmunity( Virus &v )           /* true -> 免疫獲得済み */
{
    if( min_ham_distance( tag_, v.tag_, len, v.len ) > 0 )
        return false;                           /* 最小ハミング距離が１以上なら */
    else
        return true;
}
