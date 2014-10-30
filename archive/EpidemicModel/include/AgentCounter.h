/*
 * =====================================================================================
 *
 *       Filename:  AgentCounter.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef ___AGENT_COUNTER
#define ___AGENT_COUNTER

#include "Function.h"

class Agent;

/*
 * =====================================================================================
 *        Class:  Agent
 *  Description:  エージェントのためのカウンター
 *                シングルトン
 * =====================================================================================
 */
class AgentCounter {
  public:
    static AgentCounter& Instance();                                  /* インスタンスを返す */
    void reset();
    /*-----------------------------------------------------------------------------
     *  接触回数
     *-----------------------------------------------------------------------------*/
    void countUpContact() { count_contact_++; }
    void countUpInfectionContact() { ;count_infection_contact_++; }
    void resetContact() { count_contact_ = 0; }
    void resetInfectionContact() { count_infection_contact_ = 0; }
    int getCountContact() const { return count_contact_; }
    int getCountInfectionContact() const { return count_infection_contact_; }

    void countUpRemoved() { count_removed_++; }
    void resetRemoved() { count_removed_ = 0; }
    int getCountRemoved() const { return count_removed_; }

    double calcAveValue( VECTOR(Agent*) &agents );
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    int count_contact_;
    int count_infection_contact_;
    int count_removed_;
    AgentCounter() { };                                              /* コンストラクタ */
};

#endif
