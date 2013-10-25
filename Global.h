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

#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)    /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)
#define SEPARATOR   " "

typedef int tag_t   ; 

const int WIDTH     = 120   ;                   /* ランドスケープの幅 */

const int NUM_V     = 2     ;                   /* ウイルスの種類  */
const int NUM_A     = 10000 ;                   /* エージェントの数  */

const int TAG_LEN_A = 10    ; 
const int TAG_LEN_V = 8     ;                   /* ウイルスのタグの長さ */

template < typename T >                         /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":"<<str<<std::endl; }

#endif
