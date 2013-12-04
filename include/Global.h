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

#define HAS_VIRUS_FNAME     A_hasVirus.txt                           /* 感染者の出力ファイル */
#define HAS_IMMUNITY_FNAME  A_hasImmunity.txt                        /* 免疫獲得者の出力ファイル */
#define CONTACT_FNAME       A_infectionContact.txt                   /* 接触回数の出力ファイル */
#define POPULATION_FNAME    A_population.txt                         /* 人口の出力ファイル */

typedef int tag_t;                                                   /* タグの型（通常 int ） */

// Configure ==============================================
//#define OUTPUT_HAS_VIRUS                                             /* 感染者を表示 */
//#define OUTPUT_HAS_IMMUNITY                                        /* 免疫獲得者を表示 */
//#define OUTPUT_SIR                                                   /* SIR形式で表示 */
//#define OUTPUT_CONTACT                                               /* 接触回数を表示 */
//#define OUTPUT_POPULATION                                            /* エージェントの人口推移を表示 */

//#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */
#define RANDOM_LOCATE                                                /* ランダムに再配置する */
#define AGING_AGENT
#define MATING_AGENT
#define COUPLE_TAG                                                   /* カップルタグで子供を作る */

/* term */
const int TERM                        = 500                   ;      /* 期間 */
const int OUTPUT_INTERVAL             = 1                     ;      /* 出力する間隔 */

/* landscape */
const int WIDTH                       = 30                    ;      /* ランドスケープの幅 */

/* virus */                                                          /* ウイルスの設定 -------------------- */
const int TAG_LEN_V                   = 32                    ;      /* ウイルスのタグのデフォルトの長さ */
const int NUM_V                       = 1                     ;      /* ウイルスの種類 */
const double INFECTION_RATE           = 1.0                  ;      /* デフォルトの感染率 */

const int MAX_VIRUS_AGENT_HAVE        = NUM_V                 ;      /* 最大保持ウイルス */
const int MAX_V_AGENT_INFECT_ONT_TIME = NUM_V                     ;  /* １期間で感染させるウイルスの最大数 */

/* agent */                                                          /* エージェントの設定 ---------------- */
const int TAG_LEN_A                   = 40                    ;      /* エージェントのタグ長 */
const int INIT_NUM_A                  = 100                  ;      /* 初期エージェントの数 */
const double INIT_INFECTED_RATIO      = 1.0                   ;      /* 初期感染率 */
//const double LEN_SCALE                = 1.0                   ;      /* ウイルスに対するエージェントのタグスケール */
//const int TAG_LEN_A                   = LEN_SCALE * TAG_LEN_V ;      /* エージェントのタグ長 */

const int MAX_NUM_A                   = 6000                 ;       /* 最大エージェント数 */

/* move config */                                                    /* 移動専用の設定 -------------------- */
const int MOVE_DISTANCE               = 1                     ;      /* エージェントの移動距離 */

/* aging config */                                                   /* 老化専用の設定 -------------------- */
const int MAX_AGE                     = 60                    ;      /* 寿命 */

/* mating config */                                                  /* 交配出産専用の設定 ---------------- */
const double BIRTH_RATE               = 0.10                  ;      /* 出産確率 */

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
