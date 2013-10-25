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
class Landscape;

/*
 * =====================================================================================
 *        Class:  AgentManager
 *  Description:  エージェントをまとめるクラス
 * =====================================================================================
 */
class Administrator {
    private:
        Agent *agent_;                          /* エージェントの集合 */
        Virus *virus_;
        Landscape *landscape_;

    public:
        Administrator( Agent *, Virus *, Landscape * );
        int numHasVirus( __TagInterface & );  /* v に感染している人の数 */
        int numHasAllVirus();                   /* 全ウイルスに感染している人の数 */
        int numHasImmunity( __TagInterface & ); /* v の免疫獲得者数 */

        void responseAgent();
        void relocateAgent();
        void contactAgent();
};

