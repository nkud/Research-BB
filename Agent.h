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

// class Virus;

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
        Agent( int );                           /* コンストラクタ */

        bool hasImmunity( __TagInterface & );   /* 免疫獲得しているかどうか */
        void response( __TagInterface & );      /* 免疫応答する */
};

#endif
