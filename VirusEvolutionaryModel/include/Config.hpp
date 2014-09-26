// created by Configure.py
#ifndef ___CONFIG_HPP
#define ___CONFIG_HPP

#define TERM                           5000      ///< 最大実行期間 white
#define HUMAN_INTERVAL                 1         ///< ヒト実行間隔 white
#define IMMUNE_INTERVAL                1         ///< 免疫実行間隔 white
#define HUMAN_SIZE                     1         ///< 初期ヒト数 white
#define HUMAN_LAND_WIDTH               10        ///< ヒト土地ヨコ white
#define HUMAN_LAND_HEIGHT              10        ///< ヒト土地タテ white
#define CELL_MAX_VIRUS_CAN_HAVE        100       ///< 最大保持ウイルス数 gray
#define CELL_LAND_WIDTH                40        ///< 細胞土地ヨコ gray
#define CELL_LAND_HEIGHT               40        ///< 細胞土地タテ gray
#define TCELL_LEN                      10        ///< T細胞遺伝子長 yellow
#define TCELL_MINIMUM_SIZE             10        ///< 最小T細胞数 yellow
#define TCELL_LIFESPAN                 30        ///< T細胞寿命 yellow
#define TCELL_MEMORY_RATE              100       ///< 記憶率 yellow
#define V_TAG                          5         ///< ウイルス遺伝子長 skyblue
#define V_REPRODUCTIVE_RATE            100       ///< 増殖率 skyblue
#define V_INF_RATE                     100       ///< 感染率 skyblue
#define V_MUTATION_RATE                5         ///< 突然変異率 skyblue
#define V_ONE_STEP_GROWTH_THRESHOLD    80        ///< 一段階増殖閾値 skyblue

#endif
