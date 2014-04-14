#ifndef ___MOVING_STRATEGY
#define ___MOVING_STRATEGY

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

#endif
