/*
 * =====================================================================================
 *
 *       Filename:  TagInterface.h
 *
 *    Description:  タグを持つクラスのためのインターフェイス
 *                  エージェント、ウイルス用
 *
 *         Author:  
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___TAG
#define ___TAG

#include "Global.h"

/*
 * =====================================================================================
 *        Class:  __TagInterface
 *  Description:  
 * =====================================================================================
 */
class __TagInterface
{
    private:
    public:
        int len_;

        tag_t *tag_;
        __TagInterface( int );                  /* コンストラクタ */
                                                /* タグの長さを初期化する */

        int *getTag_();                         /* タグ配列へのポインタを返す */
};

#endif
