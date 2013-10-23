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

class VirusList;
class VirusData;

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  
 * =====================================================================================
 */
class Agent : public __TagInterface
{
    private:
        VirusList *vl_;
    public:
        Agent();                                /* コンストラクタ */

        bool hasImmunity( __TagInterface & );   /* 免疫獲得済みか */
        void infection( __TagInterface & );     /* 感染プロセス */
        void response();      /* 免疫応答する（タグフリップ） */
};

struct VirusData
{
    int sp_;                                    /* スタートポイント */
    __TagInterface *v_;                          /* 保持ウイルスへのポインタ */

    VirusData *next_;                          /* 後続リストへのポインタ */
};

struct VirusList
{
    VirusData *head_;
    VirusData *crnt_;
};

#endif
