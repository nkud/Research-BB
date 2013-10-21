/*
 * =====================================================================================
 *
 *       Filename:  Virus.cpp
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
class Virus : public __TagInterface                                    /* ウイルスのクラス*/
{
    private:
//         int tag_[TAG_LEN_V];                     /* ウイルスのタグ */
    public:
        // int *getTag_();                         /* タグへのポインタを返す */
        Virus( int n ) : __TagInterface( n ) {};                                /* コンストラクタ */
};

//int *Virus :: getTag_()
//{
//    return tag_;
//}
//
//Virus :: Virus()
//{
//    FOR(i, TAG_LEN_V)
//    {
//        tag_[i] = 0;                             /* 0で初期化 */
//    }
//}

#endif
