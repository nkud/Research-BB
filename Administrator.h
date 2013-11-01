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
class Monitor;

/*
 * =====================================================================================
 *        Class:  Administrator
 *  Description:  
 * =====================================================================================
 */
class Administrator {
    private:
        Agent *agent_;                                     /* エージェントの集合 */
        Virus *virus_;                                     /* ウイルスの集合 */
        Landscape *landscape_;                             /* 土地 */
        Monitor &monitor_;

    public:
        Administrator( Agent *, Virus *, Landscape * );
        void responseAgent();                              /* 免疫応答させる */
        void relocateAgent();                              /* 再配置 */
        void contactAgent();                               /* 近隣に接触して感染させる */
        void initInfectAgentInRatio( Virus &, double );

        int numHasVirus( __TagInterface & );               /* v に感染している人の数 */
        int numHasAllVirus();                              /* 全ウイルスに感染している人の数 */
        int numHasImmunity( __TagInterface & );            /* v の免疫獲得者数 */

        void outputFile_HasVirus( const char * );          /* ファイルに出力 */
        void outputFile_InfectionContactRatio( const char * ); /* ファイルに出力 */
};

