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

#ifndef ___VIRUS
#define ___VIRUS

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
        double rate_;                           /* 感染確率 */

    public:
        Virus( const char * );                  /* コンストラクタ: タグ */
        Virus( int, double );                   /* コンストラクタ: タグ長, 感染率 */
        Virus();                                /* コンストラクタ: default */

        double getRate() { return rate_; }
        void setRate( double r ) { rate_ = r; }
};

#endif
