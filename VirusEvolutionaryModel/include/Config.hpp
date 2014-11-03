// created by Configure.py
#ifndef ___CONFIG_HPP
#define ___CONFIG_HPP

#define TERM                           10000     ///< 最大実行期間 white
#define HUMAN_INTERVAL                 1         ///< ヒト実行間隔 white
#define IMMUNE_INTERVAL                1         ///< 免疫実行間隔 white
#define HUMAN_SIZE                     1         ///< 初期ヒト数 white
#define HUMAN_LAND_WIDTH               20        ///< ヒト土地ヨコ white
#define HUMAN_LAND_HEIGHT              20        ///< ヒト土地タテ white
#define H_SYMPTOMATIC_THRESHOLD        60        ///< 発症閾値 white
#define CELL_MAX_VIRUS_CAN_HAVE        10        ///< 最大保持ウイルス数 gray
#define CELL_LAND_WIDTH                30        ///< 細胞土地ヨコ gray
#define CELL_LAND_HEIGHT               30        ///< 細胞土地タテ gray
#define CELL_REPRODUCTIVE_SPAN         0         ///< 細胞の再生産期間 gray
#define TCELL_LEN                      3         ///< T細胞遺伝子長 yellow
#define TCELL_MINIMUM_SIZE             900       ///< 最小T細胞数 yellow
#define TCELL_LIFESPAN                 20        ///< T細胞寿命 yellow
#define TCELL_MEMORY_RATE              5         ///< 記憶率 yellow
#define TCELL_CLONE_SIZE               1         ///< クローン数 yellow
#define V_TAG                          100       ///< ウイルス遺伝子長 skyblue
#define V_REPRODUCTIVE_RATE            100       ///< 増殖率 skyblue
#define V_MUTATION_RATE                30        ///< 突然変異率 skyblue
#define V_ONE_STEP_GROWTH_THRESHOLD    50        ///< 一段階増殖閾値 skyblue

#endif
