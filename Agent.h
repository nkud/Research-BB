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
class VirusBuffer;

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
        void response( __TagInterface & );      /* 免疫応答する（タグフリップ） */
};

struct VirusBuffer
{
    int sp_;                                    /* スタートポイント */
    __TagInterface *v_;                          /* 保持ウイルスへのポインタ */

    VirusBuffer *next_;                          /* 後続リストへのポインタ */
};

struct VirusList
{
    VirusBuffer *head_;
    VirusBuffer *crnt_;
};

#endif
