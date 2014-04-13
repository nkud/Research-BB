#ifndef ___AGING_STRATEGY
#define ___AGING_STRATEGY

class Agent;

/*
 * =====================================================================================
 *        Class:  __AgingStrategy
 *  Description:  老化戦略インターフェイス
 * =====================================================================================
 */
class __AgingStrategy {
  public:
    void aging();
    void setRandom();
};

#endif
