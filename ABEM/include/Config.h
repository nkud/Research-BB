#ifndef ___CONFIG
#define ___CONFIG

typedef int tag_t;                                                   /* タグの型（通常 int ） */

#if defined(__unix__) || defined(__APPLE__)
#define BENCHMARK
#endif

/*-----------------------------------------------------------------------------
 *
 *  初期設定
 *
 *-----------------------------------------------------------------------------*/
//#define AGING_AGENT
//#define MATING_AGENT

//#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */

const int TERM                      = 1000                ;           /* :期間: */
const int OUTPUT_INTERVAL           = 1                    ;         /* :出力する間隔: */
const int DATABASE_INTERVAL         = 100                  ;         /* :データベースを出力する期間: */
const int MINI_SIZE_TERM            = 200                  ;

const int WIDTH                     = 60                   ;         /* :ランドスケープの幅: */
const int A_MOVE_DISTANCE           = 2                   ;          /* :エージェントの移動距離: */

const double INFECTION_RATE         = 30.0                  ;        /* :デフォルトの感染率: */

const int A_MAX_V_CAPACITY          = 1                    ;         /* :最大保持ウイルス: */
const int A_MAX_V_INFECTED_ONE_TERM = 1                    ;         /* :１期間で感染させるウイルスの最大数: */

const int A_INIT_NUM                = 1000                  ;        /* :初期エージェントの数: */
const int A_MAX_NUM                 = A_INIT_NUM * 5       ;         /* :最大エージェント数: */

const double A_INIT_INFECTED_RATE   = 5                 ;            /* :初期感染率 0-100: */

const int A_DEFAULT_LEN             = 10                   ;         /* :エージェントのタグ長: */
const int V_DEFAULT_LEN             = 12                   ;         /* :エージェントのタグ長: */

const int V_NONINFECTIOUS_PERIOD = 0;                                /* :潜伏期間: */
const int V_INFECTIOUS_PERIOD = 3;                                   /* :症候性期間: */

const int V_MUTATION_RATE           = 30;                            /* :突然変異率: */

const int T_MAX                     = 9;                             /* :タグの最大値: */
const int BASE_TAG                  = 0;                             /* :基準タグ: */

//               12345678901234567890
#define V_TAG_0 "0000000000"
#define V_NUM 1

/*-----------------------------------------------------------------------------
 *
 *  ファイル名
 *
 *-----------------------------------------------------------------------------*/
#define HAS_VIRUS_FNAME                 "A_hasVirus.txt"             /* 感染者の出力ファイル */
#define HAS_IMMUNITY_FNAME              "A_hasImmunity.txt"          /* 免疫獲得者の出力ファイル */
#define CONTACT_FNAME                   "A_infectionContact.txt"     /* 接触回数の出力ファイル */
#define POPULATION_FNAME                "A_population.txt"           /* 人口の出力ファイル */

#endif
