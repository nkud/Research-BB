/*
 * =====================================================================================
 *
 *       Filename:  Global.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___GLOBAL
#define ___GLOBAL

#include <iostream>

#define FOR(i, m)   for(int (i)=0; (i)<(m); (i)++)    /* i: 0 ~ (m-1) */
#define SEPARATOR   " "

typedef int tag_t;

const int TAG_LEN_A = 30 ;
const int TAG_LEN_V = 20 ;                      /* ウイルスのタグの長さ */

const int NUM_A     = 10000;
const int NUM_V     = 2;

template < typename T >                         /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":"<<str<<std::endl; }

#endif
