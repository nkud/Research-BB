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

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  エージェントクラス
 * =====================================================================================
 */
class Agent : public Life
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ / デストラクタ
     *-----------------------------------------------------------------------------*/
    Agent();                                                         /* コンストラクタ  */
    Agent( __MovingStrategy *ms, int len );
    Agent( __MovingStrategy *ms, Gene *gene );
    Agent( __MovingStrategy *ms, int minl, int maxl );
    virtual ~Agent();
    /*-----------------------------------------------------------------------------
     *  免疫機構操作
     *-----------------------------------------------------------------------------*/
    ImmuneSystem &getImmuneSystem() { return *immune_system_; }
    /*-----------------------------------------------------------------------------
     *  ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    bool infection( Virus &v );                                      /* 感染プロセス  */
    int response();                                                  /* 免疫応答する（タグフリップ）  */
    void contact( Agent &other );

    bool hasVirus() const;                                           /* v に感染しているか */
    bool hasVirus( Virus &v ) const;                                 /* v に感染しているか */
    bool hasImmunity( Virus &v );                                    /* v の免疫獲得済みか  */
    int numHoldingVirus() const;                                     /* 現在保持しているウイルスの数 */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作セット
     *-----------------------------------------------------------------------------*/
    void rebirth();
    /*-----------------------------------------------------------------------------
     *  動作セット
     *-----------------------------------------------------------------------------*/
    void move();                                                     /* 移動する */
    __MovingStrategy* getMovingStrategy() const;

    void setX( int x );
    void setY( int y );
    int getX() const;
    int getY() const;
    /*-----------------------------------------------------------------------------
     *  状態
     *-----------------------------------------------------------------------------*/
    bool isSusceptible() const;                                      /* 感受性保持者、未感染者 */
    bool isIncubationPeriod() const;
    bool isSymptomaticPeriod() const;
    bool isLethal() const;
    // bool isSafe() const;

  private:
//    Gene *gene_;                                                     /* 電子タグ */
    int x_, y_;
    ImmuneSystem *immune_system_;                                    /* 免疫機構 */
    /*-----------------------------------------------------------------------------
     *  戦略
     *-----------------------------------------------------------------------------*/
    __MovingStrategy *moving_strategy_;                              /* 移動戦略 */

    Agent(const Agent& other);                                       /* コピーコンストラクタを無効化 */
    Agent& operator=(const Agent& other);                            /* 代入演算子を無効化 */
};

#endif
