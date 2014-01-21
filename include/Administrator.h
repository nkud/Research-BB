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

#ifndef ___ADMINISTRATOR
#define ___ADMINISTRATOR

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
    public:
        /*-----------------------------------------------------------------------------
         *  コンストラクタ
         *-----------------------------------------------------------------------------*/
        Administrator( VECTOR(Agent *) & , VECTOR(Virus *) &, Landscape * );   /* コンストラクタ */

        /*-----------------------------------------------------------------------------
         *  配列
         *  XXX: 露出している
         *-----------------------------------------------------------------------------*/
        VECTOR(Agent *) &agent_;                                     /* エージェントの集合 */
        VECTOR(Virus *) &virus_;                                     /* ウイルスの集合 */
        Landscape *landscape_;                                       /* 土地 */

        /*-----------------------------------------------------------------------------
         *  エージェント操作
         *-----------------------------------------------------------------------------*/
        void initInfectAgentInRatio( Virus &, double );              /* 初期感染させる */
        void responseAgent();                                        /* 免疫応答させる */
        void relocateAgent();                                        /* 再配置する */
        void moveAgent();                                            /* 移動させる */
        void contactAgent();                                         /* 近隣に接触して感染させる */
        void infectAgent();                                          /* 待機ウイルスを感染させる */

        void agingAgent();                                           /* 老化 */
        void matingAgant();                                          /* 交配、出産 */

        int getNumOfAgent() const;                                   /* エージェントの人数を返す */
        void incrementTerm();                                        /* 期間を 1 進める */
        int getTerm() const;                                         /* 進んだ期間 */


        /*-----------------------------------------------------------------------------
         *  カウント
         *-----------------------------------------------------------------------------*/
        int numHasVirus( __TagInterface & ) const;                   /* v に感染している人の数 */
        int numHasAllVirus() const;                                  /* 全ウイルスに感染している人の数 */
        int numHasImmunity( Virus &v ) const;                        /* v の免疫獲得者数 */
        int numHasAllImmunity() const;                               /* 全ウイルスの免疫獲得者数 */

        void printInitInfo() const;                                  /* 初期状態の情報を端末に出力 */

    private:
        int term_;                                                   /* 現在の期間を記録 */

        ITERATOR(Agent *) deleteAgent( ITERATOR(Agent *) &it );      /* 配列から指定のエージェントを削除 */
};

#endif
