/*
 * =====================================================================================
 *
 *       Filename:  Administrator.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"
#include "Administrator.h"
#include "Agent.h"
#include "Virus.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( Agent *a, Virus *v ) :
    agent_( a ),
    virus_( v ),
    num_agent_( NUM_A )
{}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numIsInfected( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numIsInfected( __TagInterface &v ) {
    int ret = 0;

    FOR( i, num_agent_ ) {
        if( agent_[i].isInfected( v ) ) {       /* v に感染していれば */
            ret++;                              /* インクリメント */
        }
    }
    return ret;                                 /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasImmunity( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasImmunity( __TagInterface &v ) {
    int ret = 0;

    FOR( i, num_agent_ ) {
        if (agent_[i].hasImmunity( v ) ) {
            ret++;
        }
    }
    return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: allResponse()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: allResponse() {
    FOR( i, num_agent_ ) {
        agent_[ i ].response();
    }
}
