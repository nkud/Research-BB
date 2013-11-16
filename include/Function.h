/*
 * =====================================================================================
 *
 *       Filename:  Function.h
 *
 *    Description:  
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
int flip_once( tag_t * const, const tag_t * const, const int );    /* 一回だけフリップ */

// hamming set
int ham_distance( const int * const, const int * const, const int );
int min_ham_distance_point( int *, int *, int, int );

// randomize set
int rand_interval_int( const int, const int );
int rand_array( const int );
double rand_interval_double( const double, const double );
int rand_binary();
int rand_sign();

#endif
