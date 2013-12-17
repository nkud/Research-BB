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
#define LOG(x)              do { std::cout<<"["<<#x"]: "<<x<<std::endl; }while(0);

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SEPARATOR           " "                                      /* 出力データを分割する文字 */

template < typename T >                                              /* デバッグ用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }

typedef int tag_t;                                                   /* タグの型（通常 int ） */

/*-----------------------------------------------------------------------------
 *
 *  ファイル名
 *
 *-----------------------------------------------------------------------------*/
#define HAS_VIRUS_FNAME                 "A_hasVirus.txt"             /* 感染者の出力ファイル */
#define HAS_IMMUNITY_FNAME              "A_hasImmunity.txt"          /* 免疫獲得者の出力ファイル */
#define CONTACT_FNAME                   "A_infectionContact.txt"     /* 接触回数の出力ファイル */
#define POPULATION_FNAME                "A_population.txt"           /* 人口の出力ファイル */

/*-----------------------------------------------------------------------------
 *
 *  初期設定
 *
 *-----------------------------------------------------------------------------*/

//#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */

#define RANDOM_LOCATE                                                /* ランダムに再配置する */
//#define AGING_AGENT
//#define MATING_AGENT
//#define COUPLE_TAG                                                   /* カップルタグで子供を作る */

/* 期間 */
const int TERM                        = 200000                   ;   /* 期間 */
const int OUTPUT_INTERVAL             = 1                     ;      /* 出力する間隔 */
const int MINI_SIZE_TERM              = 200;

/* 土地 */
const int WIDTH                       = 20                    ;      /* ランドスケープの幅 */

/* ウイルス */                                                          
const int TAG_LEN_V                   = 16                    ;      /* ウイルスのタグのデフォルトの長さ */
const int NUM_V                       = 2                      ;     /* ウイルスの種類 */
const double INFECTION_RATE           = 1.0                  ;       /* デフォルトの感染率 */

const int MAX_VIRUS_AGENT_HAVE        = NUM_V                 ;      /* 最大保持ウイルス */
const int MAX_V_AGENT_INFECT_ONT_TIME = 1                 ;          /* １期間で感染させるウイルスの最大数 */

/* エージェント */                                                          
const int TAG_LEN_A                   = 20                    ;      /* エージェントのタグ長 */
const int INIT_NUM_A                  = 100                  ;       /* 初期エージェントの数 */
const double INIT_INFECTED_RATIO      = 0.5                   ;      /* 初期感染率 */

const int MAX_NUM_A                   = 30000                 ;      /* 最大エージェント数 */

/* 移動 config */                                                    /* 移動専用の設定 -------------------- */
const int MOVE_DISTANCE               = 1                     ;      /* エージェントの移動距離 */

/* 寿命 config */                                                   /* 老化専用の設定 -------------------- */
const int MAX_AGE                     = 80                    ;      /* 寿命 */

/* 出産 config */                                                  /* 交配出産専用の設定 ---------------- */
const double BIRTH_RATE               = 0.03                   ;     /* 出産確率 */

#endif
