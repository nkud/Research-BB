/*
 * =====================================================================================
 *
 *       Filename:  Agent.h
 *
 *    Description:  
 *
 *         Author:  Noaki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___AGENT
#define ___AGENT

#include "Global.h"
#include "TagInterface.h"

class Virus;

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  
 * =====================================================================================
 */
class Agent : public __TagInterface
{
    private:
    public:
        Agent( int );
        bool hasImmunity( Virus & );                     /* 免疫獲得しているかどうか */

        // TODO
        // void response();                        /* 免疫応答する */
};

#endif
