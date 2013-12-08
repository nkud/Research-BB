/*
 * =====================================================================================
 *
 *       Filename:  TagInterface.h
 *
 *    Description:  タグを持つクラスのためのインターフェイス
 *                  エージェント、ウイルス用
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___TAG
#define ___TAG

#include "Global.h"

/*
 * =====================================================================================
 *        Class:  __TagInterface
 *  Description:  タグのインターフェイス
 * =====================================================================================
 */
class __TagInterface
{
    private:
    protected:
        int len_;                                                    /* タグ長 */
        tag_t *tag_;                                                 /* タグ */

    public:
        __TagInterface( int );                                       /* コンストラクタ: 長さ */
        __TagInterface( const char * );                              /* コンストラクタ: 文字列 */
        ~__TagInterface();                                           /* デストラクタ */

        tag_t *getTag() const;                                       /* タグ配列へのポインタを返す */
        void setTag( const tag_t *t, int l );                        /* タグを設定 */
        int getLen() const;                                          /* タグ長を返す */
        tag_t tagAt( const int ) const ;                             /* 特定の位置のタグの値を返す */

        void changeTagLenTo( int n );                                /* タグの長さを変える */
        
        void printTag() const;                                             /* タグを表示 */
};

#endif
