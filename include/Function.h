/*
 * =====================================================================================
 *
 *       Filename:  Function.h
 *
 *    Description:  関数セット
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___FUNCTION
#define ___FUNCTION

#include "Global.h"

// tag set
int flip_once( tag_t * const, const tag_t * const, const int );      /* 一回だけフリップ */

// hamming set
int ham_distance( const int * const, const int * const, const int ); /* ハミング距離を計算 */
int min_ham_distance_point( const int * const, const int * const, const int, const int );                /* ハミング距離が最小になる位置を返す */

// randomize set
int rand_interval_int( const int, const int );                       /* 整数の幅の乱数を返す */
double rand_interval_double( const double, const double );           /* 浮動小数点の幅の乱数を返す */
int rand_array( const int );                                         /* ０から整数までの乱数を返す */
int rand_binary();                                                   /* ０か１の乱数を返す */
int rand_sign();                                                     /* ー１か１の乱数を返す */

#endif
