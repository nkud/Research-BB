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
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define NO_DIAGONAL         0                              /* 対角線４マスを近隣に含まない */

typedef int tag_t;                                         /* タグの型（通常 int ） */

// Configure
const int TERM                          = 2000                  ; /* 期間 */
const int OUTPUT_INTERVAL               = 1                     ;
const int WIDTH                         = 50                    ; /* ランドスケープの幅 */

const int NUM_V                         = 5                     ; /* ウイルスの種類 */
const int NUM_A                         = 1000                 ; /* エージェントの数 */

const double LEN_SCALE                  = 1.0                   ; /* ウイルスに対するエージェントのタグスケール */ /* :w
:*/
const int TAG_LEN_V                     = 10                    ; /* ウイルスのタグのデフォルトの長さ */
const int TAG_LEN_A                     = LEN_SCALE * TAG_LEN_V ; /* エージェントのタグ長 */

const double INFECTION_RATE             = 0.5                   ; /* デフォルトの感染率 */
const double INIT_INFECTED_RATIO        = 0.1                   ; /* 初期感染率 */

const int MAX_VIRUS_AGENT_HAVE          = NUM_V                 ; /* 最大保持ウイルス */
const int MAX_V_AGENT_INFECT_ONT_TIME   = 1                     ; /* 一回で感染させるウイルスの最大数: infectAgent() */
//const int MAX_STAND_BY_VIRUS_AGENT_HAVE = NUM_V - 1             ; /* 最大待機ウイルス */
// ---------

template < typename T >                                    /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }
//template < typename T >                                    /* デバッグ用 */
//void debug(T str) { std::cout<<str<<":\t"<<str<<std::endl; }

#endif
