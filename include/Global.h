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

typedef int tag_t;                                         /* タグの型（通常 int ） */

// Configure
const int TERM                   = 1000                  ; /* 期間  */
const int WIDTH                  = 50                    ; /* ランドスケープの幅 */

const int NUM_V                  = 3                     ; /* ウイルスの種類  */
const int NUM_A                  = 1000                  ; /* エージェントの数  */

const double LEN_SCALE           = 5.0                   ; /* ウイルスに対するのエージェントのタグスケール */
const int TAG_LEN_V              = 10                    ; /* ウイルスのタグのでフォルトの長さ */
const int TAG_LEN_A              = LEN_SCALE * TAG_LEN_V ; /* エージェントのタグ長 */

const double INFECTION_RATE      = 0.6                   ; /* デフォルトの感染率 */
const double INIT_INFECTED_RATIO = 0.2                   ; /* 初期感染率 */
// ---------

template < typename T >                                    /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }
template < typename T >                                    /* デバッグ用 */
void debug(T str) { std::cout<<str<<":\t"<<str<<std::endl; }

#endif
