/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ham_distance
 *  Description:  ハミング距離を求める。
 *                同じ長さ限定。
 * =====================================================================================
 */

#ifndef ___FUNCTION
#define ___FUNCTION

#include "Global.h"

// hamming set
int ham_distance( int *, int *, int );
int min_ham_distance( int *, int *, int, int );

// randomize set
int rand_interval_int( int, int );
double rand_interval_double( double, double );
int rand_binary();
int rand_sign();

#endif
