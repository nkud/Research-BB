/* file name  : include/Agent.h
 * authors    : Naoki Ueda
 *
 * modifications:
 *
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

/** 
 * エージェントクラス 
 * 
 * @author Naoki Ueda
 * @version 
 */
class Agent : public Life
{
  public:
    /// コンストラクタ
    Agent();                                                         /* コンストラクタ  */
    /// コンストラクタ
    /// @param ms 移動戦略
    /// @param len タグの長さ
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
    /// @param v ウイルス
    /// @return 感染したら true
    bool infection( __VirusInterface &v );                                      /* 感染プロセス  */
    int response();                                                  /* 免疫応答する（タグフリップ）  */
    void contact( Agent &other );

    bool hasVirus() const;                                           /* v に感染しているか */
    bool hasVirus( __VirusInterface &v ) const;                                 /* v に感染しているか */
    bool hasImmunity( __VirusInterface &v );                                    /* v の免疫獲得済みか  */
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
