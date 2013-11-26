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

#include <vector>

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
        VECTOR(Agent *) &agent_;                     /* エージェントの集合 */
        VECTOR(Agent *) new_child_;                        /* 新しく生まれるエージェント */

        Virus *virus_;                                     /* ウイルスの集合 */
        Landscape *landscape_;                             /* 土地 */

        int term_;

        ITERATOR(Agent *) deleteAgent( ITERATOR(Agent *) &it );

    public:
        Administrator( VECTOR(Agent *) & , Virus *, Landscape * );

        int getNumOfAgent();
        void incrementTerm();                              /* 期間を 1 進める */
        int getTerm();                                     /* 進んだ期間 */

        void responseAgent();                              /* 免疫応答させる */
        void relocateAgent();                              /* 再配置 */
        void moveAgent();                                  /* 移動させる */
        void contactAgent();                               /* 近隣に接触して感染させる */
        void initInfectAgentInRatio( Virus &, double );
        void infectAgent();                                /* 待機ウイルスを感染させる */

        void agingAgent();
        void matingAgant();

        int numHasVirus( __TagInterface & );               /* v に感染している人の数 */
        int numHasAllVirus();                              /* 全ウイルスに感染している人の数 */
        int numHasImmunity( __TagInterface & );            /* v の免疫獲得者数 */
        int numHasAllImmunity();                           /* 全ウイルスの免疫獲得者数 */

        void printInitInfo();                              /* 初期状態の情報を端末に出力 */
        void outputFile_HasVirus( const char * );          /* ファイルに出力 */
        void outputFile_HasImmunity( const char * );       /* ファイルに出力 */
        void outputFile_InfectionContactRatio( const char * ); /* ファイルに出力 */
        void outputFile_LastLog( const char * );
        void outputFile_Population( const char * );
};

