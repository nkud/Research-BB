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

        void pushStandByVirus( __TagInterface *v ) { stand_by_list_.push_back( v ); }
        bool hasNoStandByVirus() { return stand_by_list_.empty(); }
        int getStandByListSize() { return stand_by_list_.size(); }
        __TagInterface *getStandByVirusAt( int n ) { return stand_by_list_[n]; }
        std::vector<__TagInterface *>::iterator getStandByListBeginIterator() { return stand_by_list_.begin(); }
        std::vector<__TagInterface *>::iterator getStandByListEndIterator() { return stand_by_list_.end(); }
        void eraseStandByVirus( std::vector<__TagInterface *>::iterator it ) { stand_by_list_.erase( it ); }
        void clearStandByVirus() { stand_by_list_.clear(); }

        /*
         * 保持ウイルスを操作するセット
         */
        VirusData *getVirusDataAt( int );                                      /* 保持ウイルスを返す */
        int getVirusListSize();                                                /* 保持ウイルスのリストを返す */
        void pushVirusData( VirusData * );                                     /* 保持ウイルスに追加する */
        void eraseVirusData( std::vector<VirusData *>::iterator );             /* 保持ウイルスから削除する */
        std::vector<VirusData *>::iterator getVirusListBeginIterator();        /* 先頭へのイテレータを返す */
        std::vector<VirusData *>::iterator getVirusListEndIterator();          /* 末尾へのイテレータを返す */
        bool hasNoVirusData();                                                 /* ウイルスを保持していない */
        // bool VirusDataHasNext();

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
