/*
 * =====================================================================================
 *
 *       Filename:  Function.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include "Function.h"
#include "Random.hpp"

#include <cstdlib>
#include <algorithm>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_once
 *  Description:  左から見て最初に違う位置をフリップ
 * =====================================================================================
 */
// int flip_once( tag_t * const a, const tag_t * const b, const int len ) /* 一回だけフリップ */ {
//   FOR( i, len )                                                      /* タグの長さだけ繰り返す */
//   {
//     if( *(a+i) == *(b+i) ) {
//       continue;                                                      /* 同じなら次に移動 */
//     } else {                                                         /* 違ったら */
//       *(a+i) = *(b+i);                                               /* ひとつタグをフリップ */
//       return 0;                                                      /* 終了 */
//     }
//   }
//   return -1;                                                         /* 同じタグだった */
// }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ham_distance( int *, int *, int )
 *  Description:  ハミング距離を返す
 * =====================================================================================
 */
// int ham_distance(const int * const a, const int * const b, const int n) {
//   int diff = 0;
//   FOR(i, n) {
//     if( a[i] != b[i] )
//       diff++;
//   }
//   return diff;
// }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  min_ham_distance_point
 *  Description:  最小ハミング距離が 0（なし）-> return -1
 *                最小ハミング距離が n（ >0 ）-> return sp（タグの位置）
 * =====================================================================================
 */
// int min_ham_distance_point( const int * const a, const int * const v, const int an, const int vn)           /* XXX: a > b だけ想定している */
// {
//   int minh = an;                                                     /* 最小値 */
//   int sp = 0;                                                        /* タグを比べる位置 */

//   int tm = minh;                                                     /* 初め最小ハミング距離は最大 */
//   FOR( i, an-vn+1 )                                                  /* ずらせる回数繰り返す */
//   {
//     tm = ham_distance( a+i, v, vn );                                 /* ずらした位置でのハミング距離 */
//     if( tm <= 0 ) return -1;                                          (免疫獲得済み) 
//     if( minh >= tm )                                                 /* の方が小さかったら */
//     {
//       if( minh == tm ) {                                             /* もしハミング距離が同じなら */
//         if( rand_binary() ) continue;                                /* 1/2 の確率で上書きする */
//       }
//       minh = tm;                                                     /* 最小値を更新 */
//       sp = i;                                                        /* タグの位置を記録 */
//     }
//   }
//   if( minh <= 0 ) return -1;                                         /* 免疫獲得済み */
//   return sp;                                                         /* ウイルスのタグがとりつく位置を返す */
// }


/*=============================================================================
 *
 *  RANDOMIZE SET
 *
 *=============================================================================*/
int rand_interval_int(int min, int max) {
  // int minn = min;
  // int maxx = max;
  // if( minn > maxx ) SWAP(minn, maxx);
  // return minn + (int)( rand() * (maxx - minn + 1.0) / (1.0 + RAND_MAX) );
  return Random::Instance().uniformInt(min, max);
}

double rand_interval_double(double min, double max) {
  // double minn = min;
  // double maxx = max;
  // if( minn > maxx ) SWAP(minn, maxx);
  // return minn + (double)( rand() * (maxx - minn) / (1.0 + RAND_MAX) ); /* XXX: これでいいか？ */
  return Random::Instance().uniformDouble(min, max);
}

/*-----------------------------------------------------------------------------
 *  probability( double )
 *      確率 prob で true を返す
 *      ( 0 <= prob <= 100 )
 *-----------------------------------------------------------------------------*/
bool probability( double prob ) {
  if( prob > rand_interval_double( 0, 100 ) ) {
    return true;
  } else {
    return false;
  }
}

/*-----------------------------------------------------------------------------
 *  rand_array( const int n )
 *      return (int) 0 ~ n-1
 *-----------------------------------------------------------------------------*/
int rand_array( const int n ) {
  assert( n > 0 );
  // return rand() % n;
  return rand_interval_int( 0, n-1 );
}

int rand_binary() {
  // int ret; 
  // ret = rand() % 2; 
  // return ret;
  return rand_interval_int( 0, 1 );
}

bool rand_bool() {
  if( rand_binary() == 0 )
    return true;
  else
    return false;
}

int rand_sign() {
  int ret; 
  ret = rand_bool() ? 1 : -1; 
  return ret;
}
