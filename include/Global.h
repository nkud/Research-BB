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
#include <iostream>
#include <cassert>

#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)           /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)

#define ITERATOR(type)      std::vector< type >::iterator
#define VECTOR(type)        std::vector< type >
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SEPARATOR           " "

#define HAS_VIRUS_FNAME     A_hasVirus.txt
#define HAS_IMMUNITY_FNAME  A_hasImmunity.txt
#define CONTACT_FNAME       A_infectionContact.txt

typedef int tag_t;                                                   /* タグの型（通常 int ） */

// Configure ==============================================
#define OUTPUT_HAS_VIRUS
//#define OUTPUT_HAS_IMMUNITY
#define OUTPUT_SIR                                                   /* SIR形式で表示 */
#define OUTPUT_CONTACT                                               /* 接触回数を表示 */
#define OUTPUT_POPULATION                                            /* エージェントの人口推移を表示 */

#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */
#define RANDOM_LOCATE                                                /* ランダムに再配置する */
#define COUPLE_TAG                                                   /* カップルタグで子供を作る */

const int TERM                        = 500                   ;      /* 期間 */
const int OUTPUT_INTERVAL             = 1                     ;      /* 出力する間隔 */

const int WIDTH                       = 60                    ;      /* ランドスケープの幅 */

const int MAX_AGE                     = 80                    ;      /* 寿命 */
const double BIRTH_RATE               = 0.04                  ;      /* 出産確率 */

const int NUM_V                       = 2                     ;      /* ウイルスの種類 */
const int INIT_NUM_A                  = 1200                  ;      /* 初期エージェントの数 */
const int MAX_NUM_A                   = 5000                  ;      /* 最大エージェント数 */

const double LEN_SCALE                = 2.0                   ;      /* ウイルスに対するエージェントのタグスケール */
const int TAG_LEN_V                   = 20                    ;      /* ウイルスのタグのデフォルトの長さ */
const int TAG_LEN_A                   = LEN_SCALE * TAG_LEN_V ;      /* エージェントのタグ長 */

const double INFECTION_RATE           = 0.3                   ;      /* デフォルトの感染率 */
const double INIT_INFECTED_RATIO      = 0.3                   ;      /* 初期感染率 */

const int MAX_VIRUS_AGENT_HAVE        = NUM_V                 ;      /* 最大保持ウイルス */
const int MAX_V_AGENT_INFECT_ONT_TIME = 1                     ;      /* １期間で感染させるウイルスの最大数 */

const int MOVE_DISTANCE               = 1                     ;      /* エージェントの移動距離 */
// ======================================================== 

enum __LABEL__                                                       /* ラベル */
{
    __ALIVE__,                                                       /* 生存 */
    __DEATH__,                                                       /* 死亡 */

    __MALE__,                                                        /* 男性 */
    __FEMALE__                                                       /* 女性 */
};

template < typename T >                                              /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }

#endif
