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
        VECTOR(Agent *) &agent_;                                     /* エージェントの集合 */
//        VECTOR(Agent *) new_child_;                                  /* 新しく生まれるエージェント */

        Virus *virus_;                                               /* ウイルスの集合 */
        Landscape *landscape_;                                       /* 土地 */

        int term_;                                                   /* 現在の期間を記録 */

        ITERATOR(Agent *) deleteAgent( ITERATOR(Agent *) &it );      /* 配列から指定のエージェントを削除 */

    public:
        Administrator( VECTOR(Agent *) & , Virus *, Landscape * );   /* コンストラクタ */

        int getNumOfAgent() const;
        void incrementTerm();                                        /* 期間を 1 進める */
        int getTerm() const;                                               /* 進んだ期間 */

        void initInfectAgentInRatio( Virus &, double );
        void responseAgent();                                        /* 免疫応答させる */
        void relocateAgent();                                        /* 再配置 */
        void moveAgent();                                            /* 移動させる */
        void contactAgent();                                         /* 近隣に接触して感染させる */
        void infectAgent();                                          /* 待機ウイルスを感染させる */
        void agingAgent();                                           /* 老化 */
        void matingAgant();                                          /* 交配、出産 */

        /* カウント */
        int numHasVirus( __TagInterface & ) const;                         /* v に感染している人の数 */
        int numHasAllVirus() const;                                        /* 全ウイルスに感染している人の数 */
        int numHasImmunity( __TagInterface & ) const;                      /* v の免疫獲得者数 */
        int numHasAllImmunity() const;                                     /* 全ウイルスの免疫獲得者数 */

        void printInitInfo() const;                                        /* 初期状態の情報を端末に出力 */
        void outputFile_HasVirus( const char * );                    /* ファイルに出力 */
        void outputFile_HasImmunity( const char * );                 /* ファイルに出力 */
        void outputFile_InfectionContactRatio( const char * );       /* ファイルに出力 */
        void outputFile_LastLog( const char * );                     /* ログを出力 */
        void outputFile_Population( const char * );                  /* 人口推移を出力 */
};

