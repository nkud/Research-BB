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
    protected:
        int len_;
        tag_t *tag_;

    public:
        __TagInterface( int );                  /* コンストラクタ */
                                                /* タグの長さを初期化する */
        __TagInterface( const char * );         /* コンストラクタ */

        tag_t *getTag_();                         /* タグ配列へのポインタを返す */
        int getTagLen();
        tag_t tagAt( const int );
        
        void printTag();                        /* タグを表示 */
};

#endif
