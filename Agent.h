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
#include <list>

class VirusList;
class VirusData;

/*
 * =====================================================================================
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 * =====================================================================================
 */
struct VirusData                                // 保持ウイルスデータ 
{
    __TagInterface *v_;                         // 保持ウイルスへのポインタ 
    int sp_;                                    // スタートポイント 

    VirusData( __TagInterface *v, int sp ) : v_(v), sp_(sp) {};
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
        std::list<VirusData> vlist_;
    public:
        Agent();                                // コンストラクタ 

        bool isInfected( __TagInterface & );    // ウイルス v に感染しているか
        bool hasImmunity( __TagInterface & );   // 免疫獲得済みか 
        int numOfVirus();                       // 感染しているウイルスの数

        void infection( __TagInterface & );     // 感染プロセス 
        void response();                        // 免疫応答する（タグフリップ） 
};

#endif
