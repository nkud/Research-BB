/*
 * =====================================================================================
 *
 *       Filename:  Tag.h
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
 *        Class:  Tag
 *  Description:  タグのインターフェイス
 * =====================================================================================
 */
class Tag
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ / デストラクタ
     *-----------------------------------------------------------------------------*/
    Tag( int );                                                      /* コンストラクタ: 長さ */
    Tag( int minl, int maxl );                                       /* XXX コンストラクタ: 長さ */
    Tag( const char * );                                             /* コンストラクタ: 文字列 */
    Tag( int, tag_t * );
    ~Tag();                                                          /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  タグ操作セット
     *-----------------------------------------------------------------------------*/
    void setTagRandom();                                             /* タグをランダムに設定する */
    tag_t *getTag() const;                                           /* タグ配列へのポインタを返す */
    void setTag( const tag_t *t, int l );                            /* タグを設定 */
    int getLen() const;                                              /* タグ長を返す */
    tag_t tagAt( const int ) const ;                                 /* 特定の位置のタグの値を返す */
    void changeTagLenTo( int n );                                    /* タグの長さを変える */
    void printTag() const;                                           /* タグを表示 */
    const tag_t *getTagString();

  private:
    int len_;                                                        /* タグ長 */
    tag_t *tag_;                                                     /* タグ */
};

#endif
