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
//#define NO_DIAGONAL                                                  /* 対角線４マスを近隣に含まない */

const int TERM                      = 10000          ;               /* :期間: */
const int OUTPUT_INTERVAL           = 1              ;               /* :出力する間隔: */
const int DATABASE_INTERVAL         = 100            ;               /* :データベースを出力する期間: */
const int MINI_SIZE_TERM            = 200            ;               /* :拡大画像間隔: */

const int WIDTH                     = 60             ;               /* :ランドスケープの幅: */
const int A_MOVE_DISTANCE           = 2              ;               /* :エージェントの移動距離: */

const double INFECTION_RATE         = 30.0           ;               /* :デフォルトの感染率: */

const int A_MAX_V_CAPACITY          = 1              ;               /* :最大保持ウイルス: */
const int A_MAX_V_INFECTED_ONE_TERM = 1              ;               /* :１期間で感染させるウイルスの最大数: */

const int A_INIT_NUM                = 1000           ;               /* :初期エージェントの数: */
const int A_MAX_NUM                 = A_INIT_NUM * 5 ;               /* :最大エージェント数: */

const double A_INIT_INFECTED_RATE   = 5              ;               /* :初期感染率 0-100: */

const int V_NONINFECTIOUS_PERIOD    = 10              ;               /* :<u>潜伏期間</u>: */
const int V_INFECTIOUS_PERIOD       = 40              ;               /* :<u>症候性期間</u>: */

const int V_MUTATION_RATE           = 30             ;               /* :突然変異率: */

const int T_MAX                     = 9              ;               /* :タグの最大値: */
const int T_RANDOM_MAX              = 9              ;               /* :ランダムにする時の最大値: */
const int BASE_TAG                  = 0              ;               /* :基準タグ: */

const int A_DEFAULT_LEN             = 50             ;               /* :エージェントのタグ長: */


//               SCALE
//               0        1         2         3         4         5
//               12345678901234567890123456789012345678901234567890
#define V_TAG_0 "00000000000000000000000000000000000000000000000000"
#define V_NUM 1

#endif
