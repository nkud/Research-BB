/*
 * =====================================================================================
 *
 *       Filename:  Administrator.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"

class __TagInterface;
class Agent;
class Virus;

/*
 * =====================================================================================
 *        Class:  AgentManager
 *  Description:  エージェントをまとめるクラス
 * =====================================================================================
 */
class Administrator {
    private:
        Agent *agent_;                 /* エージェントの集合 */
        Virus *virus_;
        int num_agent_;

    public:
        Administrator( Agent *, Virus * );
        int numIsInfected( __TagInterface & );  /* v に感染している人の数 */
        int numHasImmunity( __TagInterface & ); /* v の免疫獲得者数 */

        void allResponse();
};

