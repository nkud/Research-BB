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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  RandomGaussWalk :: move( int &, int & )
 * Description:  ランダムウォーク（正規分布もどき）による戦略
 *--------------------------------------------------------------------------------------
 */
void RandomGaussWalk :: move( int &x, int &y )
{
  FOR( i, getDistance() ) {
    if(probability(50)) {                                          /* 一定の確率でそのまま */
      x += rand_bool() ? 1 : -1;                                   /* 前進か後退する */
    }
    if(probability(50)) {                                          /* 一定の確率でそのまま */
      y += rand_bool() ? 1 : -1;                                   /* 前進か後退する */
    }
  }
}
