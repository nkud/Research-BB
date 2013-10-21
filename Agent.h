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
        Agent();                                /* コンストラクタ */

        bool hasImmunity( __TagInterface & );   /* 免疫獲得済みか */
        void response( __TagInterface & );      /* 免疫応答する（タグフリップ） */
};

#endif
