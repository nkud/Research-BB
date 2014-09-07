// created by Configure.py
#ifndef ___CONFIG_HPP
#define ___CONFIG_HPP

#define TERM                           2000      ///< 最大実行期間
#define HUMAN_INTERVAL                 1         ///< ヒト実行間隔
#define IMMUNE_INTERVAL                1         ///< 免疫実行間隔
#define HUMAN_SIZE                     1         ///< 初期ヒト数
#define HUMAN_LAND_WIDTH               10        ///< ヒト土地ヨコ
#define HUMAN_LAND_HEIGHT              10        ///< ヒト土地タテ
#define CELL_MAX_VIRUS_CAN_HAVE        100       ///< 最大保持ウイルス数
#define CELL_LAND_WIDTH                40        ///< 細胞土地ヨコ
#define CELL_LAND_HEIGHT               40        ///< 細胞土地タテ
#define TCELL_LEN                      10        ///< T細胞遺伝子長
#define TCELL_MINIMUM_SIZE             100       ///< 最小T細胞数
#define TCELL_LIFESPAN                 30        ///< T細胞寿命
#define TCELL_MEMORY_RATE              10        ///< 記憶率
#define V_TAG                          8         ///< ウイルス遺伝子長
#define V_REPRODUCTIVE_RATE            50        ///< 増殖率
#define V_INF_RATE                     100       ///< 感染率
#define V_ONE_STEP_GROWTH_THRESHOLD    80        ///< 一段階増殖閾値

#endif
