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

#define HAS_VIRUS_FNAME     A_hasVirus.txt
#define HAS_IMMUNITY_FNAME  A_hasImmunity.txt
#define CONTACT_FNAME       A_infectionContact.txt

typedef int tag_t; 

const int WIDTH             = 200   ; /* ランドスケープの幅 */

const int NUM_V             = 3     ; /* ウイルスの種類  */
const int NUM_A             = 10000 ; /* エージェントの数  */

const int TAG_LEN_A         = 50    ; 
const int TAG_LEN_V         = 15  ; /* ウイルスのタグのでフォルトの長さ */

const double INFECTION_RATE = 0.6   ; /* デフォルトの感染率 */

template < typename T >                         /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }
template < typename T >                         /* デバッグ用 */
void debug(T str) { std::cout<<str<<":\t"<<str<<std::endl; }

#endif
