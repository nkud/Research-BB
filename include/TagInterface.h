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
    protected:
        int len_;
        tag_t *tag_;

    public:
        __TagInterface( int );                  /* コンストラクタ: 長さ */
        __TagInterface( const char * );         /* コンストラクタ: 文字列 */

        tag_t *getTag() const;                         /* タグ配列へのポインタを返す */
        int getLen() const;
        tag_t tagAt( const int );
        
        void printTag();                        /* タグを表示 */
};

#endif
