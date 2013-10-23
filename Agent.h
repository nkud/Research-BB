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
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 *                線形リストを用いてキュー形式で
 * =====================================================================================
 */
struct VirusData                                // 保持ウイルスデータ 
{
    int sp_;                                    // スタートポイント 
    __TagInterface *v_;                         // 保持ウイルスへのポインタ 

    VirusData *next_;                           // 後続リストへのポインタ 
};

struct VirusList
{
    VirusData *head_;
    VirusData *crnt_;

    VirusData *search( __TagInterface * );      // ウイルスをリストから探す 
    void insertRear( VirusData * );             // ウイルスデータを末尾に挿入 
    void removeCurrent();                       // 着目位置のデータを削除 
    VirusData *setVirus( VirusData *, __TagInterface *, int, VirusData *); // ウイルスを初期化 
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
        VirusList *vlist_;                      // 保持ウイルスリスト 
    public:
        Agent();                                // コンストラクタ 

        bool hasImmunity( __TagInterface & );   // 免疫獲得済みか 
        void infection( __TagInterface & );     // 感染プロセス 
        void response();                        // 免疫応答する（タグフリップ） 
};

#endif
