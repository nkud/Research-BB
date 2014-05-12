/*
 * =====================================================================================
 *
 *       Filename:  Inheritance.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Agent.h"
#include "AgentStrategy.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  InheritanceLen :: childbirth
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent* InheritanceLen :: childbirth( const Agent &a, const Agent &b ) const {
  assert( isOppositeSex( a, b ) );                                   /* 同性ならエラー */

  Agent *child = new Agent(
      a.getMovingStrategy(),
      a.getChildBirthStrategy(),
      a.getLen(),
      b.getLen()
      );                                                             /* 子供を作成 */

  child->resetParam();                                               /* パラメータをリセット */

  if( a.getSex() == __FEMALE__ ) {                                   /* 母親の居場所に */
    int tx = a.getX();
    int ty = a.getY();
    child->setX( tx );                                               /* 子供を配置 */
    child->setY( ty );
  } else {
    int tx = b.getX();
    int ty = b.getY();
    child->setX( tx );
    child->setY( ty );
  }

  return child;                                                      /* 子供を返す */
}

