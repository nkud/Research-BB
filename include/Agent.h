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
#include "Virus.h"
#include <vector>

struct VirusData;
class Agent;

/*
 * =====================================================================================
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 * =====================================================================================
 */
struct VirusData                                                               /* 保持ウイルスデータ  */
{
    Virus *v_;                                                                 /* 保持ウイルスへのポインタ  */
    int sp_;                                                                   /* スタートポイント  */

    VirusData(): v_( 0 ), sp_( 0 ) {};
    VirusData( Virus &v, int sp ): v_(&v), sp_(sp) {};
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
        int x_, y_;                                                            /* 位置 */
        int age_;                                                              /* 寿命 */
        __LABEL__ sex_;                                                        /* 性別 */
        __LABEL__ life_;                                                       /* 生死 */

        std::vector<VirusData *> *vlist_;                                      /* 保持ウイルスのリスト */
        std::vector<Virus *> *stand_by_list_;                                  /* 待機ウイルスリスト */

    public:
        Agent();                                                               /* コンストラクタ  */
        ~Agent();

        void resetParam();

        /* 保持ウイルスを操作するセット */
        VirusData *getVirusDataAt( int ) const;                                /* 指定の保持ウイルスを返す */
        int getVirusListSize() const;                                          /* 保持ウイルスのリストを返す */
        void pushVirusData( VirusData * );                                     /* 保持ウイルスに追加する */
        void eraseVirusData( std::vector<VirusData *>::iterator );             /* 指定の保持ウイルスを削除する */
        bool hasNoVirusData() const;                                           /* ウイルスを保持していない */
        std::vector<VirusData *>::iterator getVirusListIteratorBegin();        /* 先頭へのイテレータを返す */
        std::vector<VirusData *>::iterator getVirusListIteratorEnd();          /* 末尾へのイテレータを返す */

        /* 待機ウイルス操作セット */
        Virus *getStandByVirusAt( int n ) const;                               /* 指定の待機ウイルスを返す */
        int getStandByListSize() const;                                        /* 待機ウイルスの数を返す */
        void pushStandByVirus( Virus *v );                                     /* 待機ウイルスに追加する */
        void eraseStandByVirus( std::vector<Virus *>::iterator it );           /* 指定の待機ウイルスを削除 */
        void clearStandByVirus();                                              /* 待機ウイルスをすべて削除 */
        bool hasNoStandByVirus() const;                                        /* ウイルスを保持していない */
        std::vector<Virus *>::iterator getStandByListIteratorBegin();          /* 先頭へのイテレータを返す */
        std::vector<Virus *>::iterator getStandByListIteratorEnd();            /* 末尾へのイテレータを返す */

        /* 位置 */
        void setX( int ); int getX() const;                                    /* セッタ、ゲッタ */
        void setY( int ); int getY() const;
        __LABEL__ getSex() const;

        int aging();                                                           /* 年をとる */
        int getAge() const;
        void setLife( __LABEL__ l );
        bool isAlive() const;
        bool isDead() const;

        bool infection( Virus &v );                                             /* 感染プロセス  */
        void response();                                                       /* 免疫応答する（タグフリップ）  */

        bool isInfected( __TagInterface &v )  const  ;                          /* v に感染しているか */
        bool hasVirus( __TagInterface &v )    const  ;                          /* v に感染しているか */
        bool hasImmunity( __TagInterface &v ) const  ;                          /* v の免疫獲得済みか  */
        int numHoldingVirus()                const  ;                          /* 現在保持しているウイルスの数 */
};

void die( Agent &a );                                                          /* 死亡処理 */
void childbirth( Agent &child, const Agent &a, const Agent &b );                           /* 親から子を作成 */
bool isOppositeSex( const Agent &a, const Agent &b );                          /* 異性かどうか */

#endif
