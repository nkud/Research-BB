/*
 * =====================================================================================
 *
 *       Filename:  Agent.h
 *
 *    Description:  エージェントクラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___AGENT
#define ___AGENT

#include "Global.h"
#include "TagInterface.h"
#include <list>

class VirusData;
class Agent;

/*
 * =====================================================================================
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 * =====================================================================================
 */
struct VirusData                                /* 保持ウイルスデータ  */
{
    __TagInterface *v_;                         /* 保持ウイルスへのポインタ  */
    int sp_;                                    /* スタートポイント  */

    VirusData( __TagInterface *v, int sp ) :    /* データの初期化 */
        v_(v), sp_(sp) {};
};

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  
 * =====================================================================================
 */

class Agent : public __TagInterface
{
    private:
        std::list<VirusData> vlist_;            /* 保持ウイルスのリスト */

    public:
        Agent();                                /* コンストラクタ  */

        void infection( __TagInterface & );     /* 感染プロセス  */
        void response();                        /* 免疫応答する（タグフリップ）  */

        bool isInfected( __TagInterface & );    /* v に感染しているか */
        bool hasImmunity( __TagInterface & );   /* v の免疫獲得済みか  */
        int numHoldingVirus();                  /* 現在保持しているウイルスの数 */
};

/*
 * =====================================================================================
 *        Class:  AgentManager
 *  Description:  エージェントをまとめる
 * =====================================================================================
 */
class AgentManager {
    private:
        Agent *agent_;                 /* エージェントの集合 */
        int num_agent_;

    public:
        AgentManager( Agent *a ) : agent_( a ), num_agent_( NUM_A ) {}
        int numIsInfected( __TagInterface & );  /* v に感染している人の数 */
        int numHasImmunity( __TagInterface & ); /* v の免疫獲得者数 */
};

#endif
