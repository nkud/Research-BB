/*
 * =====================================================================================
 *
 *       Filename:  AgentManager.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___AGENT_MANAGER
#define ___AGENT_MANAGER

class Agent;
class __MovingStrategy;
class __ChildBirthStrategy;
class Gene;

class AgentManager {
  public:
    AgentManager( VECTOR(Agent *) &agents );
    /*-----------------------------------------------------------------------------
     *  初期化
     *-----------------------------------------------------------------------------*/
    virtual void initAgent( __MovingStrategy *, __ChildBirthStrategy *, Gene *, int num );
    virtual void initInfectAgentInRatio( Virus &, double );          /* 初期感染させる */
    /*-----------------------------------------------------------------------------
     *  集団的処理
     *-----------------------------------------------------------------------------*/
    virtual void migrate();                                          /* 移動 */

    virtual void contact();                                          /* 接触 */
    virtual void infect();                                           /* 感染 */
    virtual void response();                                         /* 免疫応答 */

    virtual void aging();                                            /* 老化 */
    virtual void mating();                                           /* 交配 */

    int numHasVirus();

    int numIsIncubation() const;
    int numIsCrisis() const;

    void printInitInfo() const;                                      /* 初期状態の情報を端末に出力 */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    ITERATOR(Agent *) getAgentIteratorBegin() { return agents_.begin(); }
    ITERATOR(Agent *) getAgentIteratorEnd() { return agents_.end(); }
    int getAgentSize() const { return agents_.size(); }
    ITERATOR(Agent *) deleteAgent( ITERATOR(Agent *) &it );

  private:
    VECTOR(Agent *) &agents_;
};

#endif
