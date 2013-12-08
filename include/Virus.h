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

#include "TagInterface.h"

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  
 * =====================================================================================
 */
class Virus : public __TagInterface                                  /* ウイルスのクラス*/
{
        double rate_;                                                /* 感染確率 */

    public:
        Virus( const char * );                                       /* コンストラクタ: タグ */
        Virus( int, double );                                        /* コンストラクタ: タグ長, 感染率 */
        Virus();                                                     /* コンストラクタ: default */

        double getRate() const;                                      /* 感染確率を返す */
        void setRate( const double r );                              /* 感染確率を設定 */

        int searchStartPoint( const __TagInterface & ) const;                    /* タグに取り付く位置を返す */
};

#endif
