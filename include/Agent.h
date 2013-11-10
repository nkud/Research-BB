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
struct VirusData                                                               /* 保持ウイルスデータ  */
{
    __TagInterface *v_;                                                        /* 保持ウイルスへのポインタ  */
    int sp_;                                                                   /* スタートポイント  */

    VirusData(): v_( 0 ), sp_( 0 ) {};
    VirusData( __TagInterface &v, int sp ): v_(&v), sp_(sp) {};
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

        int x_, y_;
        std::vector<VirusData *> vlist_;                                       /* 保持ウイルスのリスト */
        std::vector<__TagInterface *> stand_by_list_;

    public:
        Agent();                                                               /* コンストラクタ  */

        /* 待機ウイルス操作セット */
        __TagInterface *getStandByVirusAt( int n );                            /* 指定の待機ウイルスを返す */
        int getStandByListSize();                                              /* 待機ウイルスの数を返す */
        void pushStandByVirus( __TagInterface *v );                            /* 待機ウイルスに追加する */
        void eraseStandByVirus( std::vector<__TagInterface *>::iterator it );  /* 指定の待機ウイルスを削除 */
        void clearStandByVirus();                                              /* 待機ウイルスをすべて削除 */
        bool hasNoStandByVirus();                                              /* ウイルスを保持していない */
        std::vector<__TagInterface *>::iterator getStandByListBeginIterator(); /* 先頭へのイテレータを返す */
        std::vector<__TagInterface *>::iterator getStandByListEndIterator();   /* 末尾へのイテレータを返す */

        /* 保持ウイルスを操作するセット */
        VirusData *getVirusDataAt( int );                                      /* 指定の保持ウイルスを返す */
        int getVirusListSize();                                                /* 保持ウイルスのリストを返す */
        void pushVirusData( VirusData * );                                     /* 保持ウイルスに追加する */
        void eraseVirusData( std::vector<VirusData *>::iterator );             /* 指定の保持ウイルスを削除する */
        bool hasNoVirusData();                                                 /* ウイルスを保持していない */
        std::vector<VirusData *>::iterator getVirusListBeginIterator();        /* 先頭へのイテレータを返す */
        std::vector<VirusData *>::iterator getVirusListEndIterator();          /* 末尾へのイテレータを返す */

        void setX( int ); int getX();                                          /* セッタ、ゲッタ */
        void setY( int ); int getY();

        bool infection( __TagInterface & );                                    /* 感染プロセス  */
        void response();                                                       /* 免疫応答する（タグフリップ）  */

        bool isInfected( __TagInterface & );                                   /* v に感染しているか */
        bool hasVirus( __TagInterface & );                                     /* v に感染しているか */
        bool hasImmunity( __TagInterface & );                                  /* v の免疫獲得済みか  */
        int numHoldingVirus();                                                 /* 現在保持しているウイルスの数 */
};

#endif
