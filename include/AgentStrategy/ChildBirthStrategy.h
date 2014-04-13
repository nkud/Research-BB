#ifndef ___CHILDBIRTH_STRATEGY
#define ___CHILDBIRTH_STRATEGY

class Agent;

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

#endif
