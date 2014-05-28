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

#include "Global.h"

class Agent;
class __MovingStrategy;
class __ChildBirthStrategy;

class AgentManager {
  public:
    AgentManager( VECTOR(Agent *) &agents );
    /*-----------------------------------------------------------------------------
     *  初期化
     *-----------------------------------------------------------------------------*/
    virtual void initAgent( __MovingStrategy *, __ChildBirthStrategy *, int len, int num );
    /*-----------------------------------------------------------------------------
     *  集団的処理
     *-----------------------------------------------------------------------------*/
    virtual void migrate();                                          /* 移動 */

    virtual void contact();                                          /* 接触 */
    virtual void infect();                                           /* 感染 */
    virtual void response();                                         /* 免疫応答 */

    virtual void aging();                                            /* 老化 */
    virtual void mating();                                           /* 交配 */
    /*-----------------------------------------------------------------------------
     *  パラメータ操作
     *-----------------------------------------------------------------------------*/
    ITERATOR(Agent *) getAgentIteratorBegin() { return agents_.begin(); }
    ITERATOR(Agent *) getAgentIteratorEnd() { return agents_.begin(); }
    int getAgentSize() { return agents_.size(); }
    ITERATOR(Agent *) deleteAgent( ITERATOR(Agent *) &it );

  private:
    VECTOR(Agent *) agents_;
};

#endif
