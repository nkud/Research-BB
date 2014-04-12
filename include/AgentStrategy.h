/*
 * =====================================================================================
 *
 *       Filename:  AgentStrategy.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___AGENT_STRATEGY
#define ___AGENT_STRATEGY

class Agent;

/*
 * =====================================================================================
 *        Class:  __MovingStrategy
 *  Description:  移動戦略インターフェイス
 * =====================================================================================
 */
class __MovingStrategy {                                             /* 移動戦略インターフェイス */
  public:
    virtual void move( int &x, int &y ) = 0;

    virtual const __MovingStrategy* getStrategy() const { return this; }
};
/*-----------------------------------------------------------------------------
 *  再配置
 *-----------------------------------------------------------------------------*/
class Relocate : public __MovingStrategy {                           /* 再配置による移動戦略 */
  public:
    virtual void move( int &x, int &y );
};
/*-----------------------------------------------------------------------------
 *  ランダムウォーク
 *-----------------------------------------------------------------------------*/
class RandomWalk : public __MovingStrategy {                         /* ランダムウォークによる移動戦略 */
  public:
    RandomWalk( int dis ) : distance_( dis ) {}                      /* 距離を設定する */
    virtual void move( int &x, int &y );
  private:
    const int distance_;
};

/*
 * =====================================================================================
 *        Class:  __ChildBirthStrategy
 *  Description:  子孫戦略インターフェイス
 * =====================================================================================
 */
class __ChildBirthStrategy {
  public:
    virtual Agent* childbirth( const Agent &a, const Agent &b ) const = 0;         /* 親から子を作成 */

    virtual const __ChildBirthStrategy* getStrategy() const { return this; }
};

/*-----------------------------------------------------------------------------
 *  カップルタグ
 *-----------------------------------------------------------------------------*/
class CoupleTag : public __ChildBirthStrategy {
  public:
    virtual Agent* childbirth( const Agent &a, const Agent &b ) const;         /* 親から子を作成 */
};
/*-----------------------------------------------------------------------------
 *  タグ長遺伝
 *-----------------------------------------------------------------------------*/
class InheritanceLen : public __ChildBirthStrategy {
  public:
    virtual Agent* childbirth( const Agent &a, const Agent &b ) const;         /* 親から子を作成 */
};

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

/* =====================================================================================
 *        Class:  __ResponseStrategy
 *  Description:  免疫応答戦略インターフェイス
 * ================================================================================== */
class __ImmuneSystemStrategy {
  public:
    virtual void response(Agent &self) = 0;
    virtual bool infection(Agent &self, Virus &v ) = 0;
};

class TagFlip : public __ImmuneSystemStrategy {
  public:
    virtual void response(Agent &self);
    virtual bool infection(Agent &self, Virus &v );
};

#endif
