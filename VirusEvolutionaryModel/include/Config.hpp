// created by Configure.py
#ifndef ___CONFIG_HPP
#define ___CONFIG_HPP

#define TERM                           3000      ///< 最大実行期間 white
#define HUMAN_INTERVAL                 1         ///< ヒト実行間隔 white
#define IMMUNE_INTERVAL                1         ///< 免疫実行間隔 white
#define HUMAN_SIZE                     1         ///< 初期ヒト数 white
#define HUMAN_LAND_WIDTH               30        ///< ヒト土地ヨコ white
#define HUMAN_LAND_HEIGHT              30        ///< ヒト土地タテ white
#define H_SYMPTOMATIC_THRESHOLD        60        ///< 発症閾値 white
#define CELL_MAX_VIRUS_CAN_HAVE        100       ///< 最大保持ウイルス数 gray
#define CELL_LAND_WIDTH                30        ///< 細胞土地ヨコ gray
#define CELL_LAND_HEIGHT               30        ///< 細胞土地タテ gray
#define TCELL_LEN                      8         ///< T細胞遺伝子長 yellow
#define TCELL_MINIMUM_SIZE             100       ///< 最小T細胞数 yellow
#define TCELL_LIFESPAN                 5         ///< T細胞寿命 yellow
#define TCELL_MEMORY_RATE              10        ///< 記憶率 yellow
#define TCELL_CLONE_SIZE               1         ///< クローン数 yellow
#define V_TAG                          8         ///< ウイルス遺伝子長 skyblue
#define V_REPRODUCTIVE_RATE            80        ///< 増殖率 skyblue
#define V_MUTATION_RATE                10        ///< 突然変異率 skyblue
#define V_ONE_STEP_GROWTH_THRESHOLD    30        ///< 一段階増殖閾値 skyblue

#endif
