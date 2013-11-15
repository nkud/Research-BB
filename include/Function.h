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
int flip_once( tag_t *, tag_t *, const int len );    /* 一回だけフリップ */

// hamming set
int ham_distance( const int *, const int *, const int );
int min_ham_distance( int *, int *, int, int );

// randomize set
int rand_interval_int( int, int );
int rand_array( int );
double rand_interval_double( double, double );
int rand_binary();
int rand_sign();

#endif
