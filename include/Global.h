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
#include <vector>

#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++) /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)
#define SEPARATOR   " "

#define HAS_VIRUS_FNAME     A_hasVirus.txt
#define HAS_IMMUNITY_FNAME  A_hasImmunity.txt
#define CONTACT_FNAME       A_infectionContact.txt

#define ITERATOR(type)      std::vector< type >::iterator

typedef int tag_t; 

// Configure
const int WIDTH                = 20                    ;   /* ランドスケープの幅 */

const int NUM_V                = 4                     ;   /* ウイルスの種類  */
const int NUM_A                = 100                   ;   /* エージェントの数  */

const double LEN_SCALE         = 3                     ; 
const int TAG_LEN_V            = 20                    ;   /* ウイルスのタグのでフォルトの長さ */
const int TAG_LEN_A            = LEN_SCALE * TAG_LEN_V ; 

const double INFECTION_RATE    = 0.8                   ;   /* デフォルトの感染率 */
const double INIT_INFECT_RATIO = 0.2                   ;   /* 初期感染率 */
// ---------

template < typename T >                                    /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }
template < typename T >                                    /* デバッグ用 */
void debug(T str) { std::cout<<str<<":\t"<<str<<std::endl; }

#endif
