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

#include "Gene.h"
#include "Virus.h"
#include "AgentStrategy.h"
#include "ImmuneSystem.h"

#include <vector>
#include <map>

class __MovingStrategy;
class __ChildBirthStrategy;

/*-----------------------------------------------------------------------------
 *  ラベル
 *-----------------------------------------------------------------------------*/
enum __LABEL__                                                       /* ラベル */
{
  __ALIVE__,                                                         /* 生存 */
  __DEATH__,                                                         /* 死亡 */

  __MALE__,                                                          /* 男性 */
  __FEMALE__                                                         /* 女性 */
};

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  エージェントクラス
 * =====================================================================================
 */
class Agent
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ / デストラクタ
     *-----------------------------------------------------------------------------*/
    Agent();                                                         /* コンストラクタ  */
    Agent( __MovingStrategy *ms, __ChildBirthStrategy *cbs, int len );
    Agent( __MovingStrategy *ms, __ChildBirthStrategy *cbs, Gene *gene );
    Agent( __MovingStrategy *ms, __ChildBirthStrategy *cbs, int minl, int maxl );
    virtual ~Agent();
    /*-----------------------------------------------------------------------------
     *  免疫機構操作
     *-----------------------------------------------------------------------------*/
    ImmuneSystem *getImmuneSystem() { return immune_system_; }
    /*-----------------------------------------------------------------------------
     *  ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    bool infection( Virus &v );                                      /* 感染プロセス  */
    int response();                                                 /* 免疫応答する（タグフリップ）  */
    void contact( Agent &other );

    bool hasVirus() const;                                           /* v に感染しているか */
    bool hasVirus( Virus &v ) const;                                 /* v に感染しているか */
    bool hasImmunity( Virus &v );                        /* v の免疫獲得済みか  */
    int numHoldingVirus() const;                                     /* 現在保持しているウイルスの数 */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作セット
     *-----------------------------------------------------------------------------*/
    void resetParam();                                               /* パラメータをリセット */
    void rebirth();
    void setX( int ); int getX() const;                              /* セッタ、ゲッタ */
    void setY( int ); int getY() const;
    __LABEL__ getSex() const;
    /*-----------------------------------------------------------------------------
     *  動作セット
     *-----------------------------------------------------------------------------*/
    void move();                                                     /* 移動する */
    __MovingStrategy* getMovingStrategy() const;
    int aging();                                                     /* 年をとる */

    int getAge() const;                                              /* 年齢を取得する */
    void setAge(int n) { age_ = n; }

    bool hasAbilityToChildbirth() const;                             /* 出産可能か */
    void setLife( __LABEL__ life );                                  /* 生死を設定する */

    /*-----------------------------------------------------------------------------
     *  状態
     *-----------------------------------------------------------------------------*/
    bool isSusceptible() const;                                      /* 感受性保持者、未感染者 */
    bool isIncubationPeriod() const;
    bool isSymptomaticPeriod() const;
    bool isLethal() const;
    // bool isSafe() const;
    /*-----------------------------------------------------------------------------
     *  交配・出産関連セット
     *-----------------------------------------------------------------------------*/
    Agent* childBirthWith( const Agent &partner ) const;             /* パートナーとの子を作成して返す */
    __ChildBirthStrategy* getChildBirthStrategy() const;
    bool hasAlreadyGiveBirth();                                      /* 出産済みかどうか */
    void setGiveBirth();                                             /* 出産後にする */
    void resetGiveBirth();                                           /* 出産したかをリセット */
    /*-----------------------------------------------------------------------------
     *  タグ操作セット
     *-----------------------------------------------------------------------------*/
    int getLen() const { return gene_->getLen(); }
    tag_t tagAt(int n) const { return gene_->tagAt(n); }
    Gene & getGene() { return *gene_; }

  private:
    bool give_birth_;                                                /* 出産済みか */

    int x_, y_;                                                      /* 位置 */
    int age_;                                                        /* 寿命 */

    __LABEL__ sex_;                                                  /* 性別 */
    __LABEL__ life_;                                                 /* 生死 */

    Gene *gene_;                                                     /* 電子タグ */
    ImmuneSystem *immune_system_;                                    /* 免疫機構 */
    /*-----------------------------------------------------------------------------
     *  戦略
     *-----------------------------------------------------------------------------*/
    __MovingStrategy *moving_strategy_;                              /* 移動戦略 */
    __ChildBirthStrategy *childbirth_strategy_;                      /* 子孫戦略 */

    Agent(const Agent& other);                                       /* コピーコンストラクタを無効化 */
    Agent& operator=(const Agent& other);                            /* 代入演算子を無効化 */
};
/*-----------------------------------------------------------------------------
 *  エージェントを操作
 *-----------------------------------------------------------------------------*/
bool isOppositeSex( const Agent &a, const Agent &b );                /* 異性かどうか */

#endif
