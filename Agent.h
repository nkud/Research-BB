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
#include <vector>

struct VirusData;
class Agent;
class Monitor;

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

    VirusData(): v_( 0 ), sp_( 0 ) {};
    VirusData( __TagInterface *v, int sp ):     /* データの初期化 */
        v_(v), sp_(sp) {};
};

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  エージェントクラス
 * =====================================================================================
 */

class Agent : public __TagInterface
{
    private:
        Monitor &monitor_;

    public:
        int x_, y_;
        std::vector<VirusData> vlist_;          /* 保持ウイルスのリスト */
        std::vector<__TagInterface *> stand_by_virus_;
        Agent();                                /* コンストラクタ  */

        void infection( __TagInterface & );     /* 感染プロセス  */
        void response();                        /* 免疫応答する（タグフリップ）  */

        bool isInfected( __TagInterface & );    /* v に感染しているか */
        bool hasVirus( __TagInterface & );      /* v に感染しているか */

        bool hasImmunity( __TagInterface & );   /* v の免疫獲得済みか  */
        int numHoldingVirus();                  /* 現在保持しているウイルスの数 */
};

#endif
