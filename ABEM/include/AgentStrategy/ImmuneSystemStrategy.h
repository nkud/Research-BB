#ifndef ___IMMUNESYSTEM_STRATEGY
#define ___IMMUNESYSTEM_STRATEGY

class Agent;

/* =====================================================================================
 *        Class:  __ImmuneSystemStrategy
 *  Description:  免疫応答戦略インターフェイス
 * ================================================================================== */
class __ImmuneSystemStrategy {
  public:
    virtual void response(Agent &self) = 0;
    virtual bool infection(Agent &self, Virus &v ) = 0;
};

/*-----------------------------------------------------------------------------
 *  タグフリップ
 *-----------------------------------------------------------------------------*/
class TagFlip : public __ImmuneSystemStrategy {
  public:
    virtual void response(Agent &self);
    virtual bool infection(Agent &self, Virus &v );
};

#endif
