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

typedef int tag_t;                                         /* タグの型（通常 int ） */

// Configure ==============================================
#define NO_DIAGONAL         1                              /* 対角線４マスを近隣に含まない */
#define RANDOM_LOCATE       0

const int TERM                          = 300                   ; /* 期間 */
const int OUTPUT_INTERVAL               = 1                     ; /* 出力する間隔 */

/* landscape */
const int WIDTH                         = 15                    ; /* ランドスケープの幅 */

const int NUM_V                         = 2                     ; /* ウイルスの種類 */
const int NUM_A                         = 100                    ; /* エージェントの数 */

const double LEN_SCALE                  = 2.0                  ; /* ウイルスに対するエージェントのタグスケール */
const int TAG_LEN_V                     = 10                    ; /* ウイルスのタグのデフォルトの長さ */
const int TAG_LEN_A                     = LEN_SCALE * TAG_LEN_V ; /* エージェントのタグ長 */

/* rate */
const double INFECTION_RATE             = 1.0                   ; /* デフォルトの感染率 */
const double INIT_INFECTED_RATIO        = 0.1                   ; /* 初期感染率 */

/* max */
const int MAX_VIRUS_AGENT_HAVE          = NUM_V                 ; /* 最大保持ウイルス */
const int MAX_V_AGENT_INFECT_ONT_TIME   = 1                     ; /* １期間で感染させるウイルスの最大数 */
//const int MAX_STAND_BY_VIRUS_AGENT_HAVE = NUM_V - 1             ; /* 最大待機ウイルス */

const int MOVE_DISTANCE                 = 1                     ; /* エージェントの移動距離 */
// ======================================================== 

template < typename T >                                    /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }
//template < typename T >                                    /* デバッグ用 */
//void debug(T str) { std::cout<<str<<":\t"<<str<<std::endl; }

#endif
