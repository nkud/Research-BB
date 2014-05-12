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

#if defined(__unix__) || defined(__APPLE__)
#define ___BENCHMARK
#endif

/*-----------------------------------------------------------------------------
 *
 *  初期設定
 *
 *-----------------------------------------------------------------------------*/
//#define AGING_AGENT
//#define MATING_AGENT

//#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */

const int TERM                      = 500                 ;         /* 期間 */
const int OUTPUT_INTERVAL           = 1                    ;         /* 出力する間隔 */
const int MINI_SIZE_TERM            = 200                  ;

const int WIDTH                     = 40                   ;         /* ランドスケープの幅 */

const double INFECTION_RATE         = 1.0                  ;         /* デフォルトの感染率 */

const int A_MAX_V_CAN_HAVE          = 2                    ;         /* 最大保持ウイルス */
const int A_MAX_V_INFECTED_ONE_TERM = 1                    ;         /* １期間で感染させるウイルスの最大数 */

const int A_INIT_NUM                = 1000                  ;        /* 初期エージェントの数 */

const double A_INIT_INFECTED_RATE   = 3                  ;         /* 初期感染率 */

const int A_DEFAULT_LEN             = 20                   ;         /* エージェントのタグ長 */
const int V_DEFAULT_LEN             = 18                   ;         /* エージェントのタグ長 */

#define V_TAG_0 "000000000000"
#define V_TAG_1 "111111111111"
#define V_NUM 2

const int A_MAX_NUM                 = A_INIT_NUM * 5       ;         /* 最大エージェント数 */

const int A_MOVE_DISTANCE           = 10                   ;         /* エージェントの移動距離 */

const int A_MAX_AGE                 = 10                  ;         /* 寿命 */

const double A_BIRTH_RATE           = 0.5                  ;         /* 出生率 */
const int A_BIRTH_AGE_FROM          = int(A_MAX_AGE * 0.2) ;
const int A_BIRTH_AGE_TO            = int(A_MAX_AGE * 0.6) ;

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
 *  インクルードファイル
 *
 *-----------------------------------------------------------------------------*/

#include <iostream>
#include <vector>
#include <iostream>
#include <cassert>

#define FOR(i, m)           for(unsigned int (i)=0; (i)<(m); (i)++)  /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)
#define LOG(x)              do { std::cout<<"["<<#x"]: "<<x<<std::endl; }while(0);

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SEPARATOR           " "                                      /* 出力データを分割する文字 */

typedef int tag_t;                                                   /* タグの型（通常 int ） */

#endif
