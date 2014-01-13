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

#include "Agent.h"

class Agent;

/*
 * =====================================================================================
 *        Class:  __AgingStrategy
 *  Description:  老化戦略インターフェイス
 * =====================================================================================
 */
class __AgingStrategy {
    void aging();
    void setRandom();
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
};

/*-----------------------------------------------------------------------------
 *  カップルタグ
 *-----------------------------------------------------------------------------*/
class CoupleTag : public __ChildBirthStrategy {
    public:
        virtual Agent* childbirth( const Agent &a, const Agent &b ) const;         /* 親から子を作成 */
};

/*
 * =====================================================================================
 *        Class:  __MovingStrategy
 *  Description:  移動戦略インターフェイス
 * =====================================================================================
 */
class __MovingStrategy {                                             /* 移動戦略インターフェイス */
    public:
        virtual void move( int &x, int &y ) = 0;
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
        RandomWalk( int dis ) : distance_( dis ) {}                  /* 距離を設定する */
        virtual void move( int &x, int &y );
    private:
        int distance_;
};


#endif
