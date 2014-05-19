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
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    AgentCounter() { };                                              /* コンストラクタ */
};

#endif