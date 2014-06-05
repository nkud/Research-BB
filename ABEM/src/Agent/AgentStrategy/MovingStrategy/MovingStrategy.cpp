/*
 * =====================================================================================
 *
 *       Filename:  MovingStrategy.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include "Agent.h"
#include "AgentStrategy.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Relocate :: move( int &, int & )
 * Description:  再配置による戦略
 *--------------------------------------------------------------------------------------
 */
void Relocate :: move( int &x, int &y ) {
  x = rand_interval_int( 0, WIDTH-1 );
  y = rand_interval_int( 0, WIDTH-1 );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  RandomWalk :: move( int &, int & )
 * Description:  ランダムウォークによる戦略
 *--------------------------------------------------------------------------------------
 */
void RandomWalk :: move( int &x, int &y ) {
  x += rand_interval_int( -distance_, distance_ );
  y += rand_interval_int( -distance_, distance_ );
}