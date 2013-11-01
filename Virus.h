/*
 * =====================================================================================
 *
 *       Filename:  Virus.h
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef VIRUS
#define VIRUS

#include "Global.h"
#include "TagInterface.h"

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  
 * =====================================================================================
 */
class Virus : public __TagInterface             /* ウイルスのクラス*/
{
    public:
        Virus( const char * );                  /* コンストラクタ: タグ */
        Virus( int, double );                   /* コンストラクタ: タグ長, 感染率 */
        Virus();                                /* コンストラクタ: default */

        double rate_;                           /* 感染確率 */
};

#endif
