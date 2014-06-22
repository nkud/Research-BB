/*
 * =====================================================================================
 *
 *       Filename:  Gene.h
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

#include "Config.h"
#include "Function.h"

/*
 * =====================================================================================
 *        Class:  Gene
 *  Description:  遺伝子
 * =====================================================================================
 */
class Gene
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ / デストラクタ
     *-----------------------------------------------------------------------------*/
    Gene( int );                                                      /* コンストラクタ: 長さ */
    Gene( int minl, int maxl );                                       /* XXX コンストラクタ: 長さ */
    Gene( const char * );                                             /* コンストラクタ: 文字列 */
    // XXX: コピーコンストラクタにする
    Gene( Gene & );
    virtual ~Gene();                                                          /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  タグ操作セット
     *-----------------------------------------------------------------------------*/
    void setTagRandom();                                             /* タグをランダムに設定する */
    tag_t *getTag() const;                                           /* タグ配列へのポインタを返す */
    void setTag( const tag_t *t, int l );                            /* タグを設定 */
    int getLen() const;                                              /* タグ長を返す */
    virtual tag_t tagAt( const int ) const ;                                 /* 特定の位置のタグの値を返す */
    void changeTagLenTo( int n );                                    /* タグの長さを変える */
    void printTag() const;                                           /* タグを表示 */
    // const tag_t *getTagString();

    int pointOfMinHamDistance( const Gene & ) const;
    int flipToGeneAtPosition( const Gene &, int pos );
    int hamDistance( const Gene &, int pos ) const;

    void changeTagAtTo( int at, int num );

    void mutation();                                                 /* 突然変異を起こす */
    void mutation( double );                                         /* 突然変異を起こす */

    int value();

    Gene *newCopy() const {
        Gene *copy = new Gene(getLen());
        FOR( i, getLen() ) {
            copy->changeTagAtTo(i, tagAt(i));
        }
        return copy;
    }

  private:
    int len_;                                                        /* タグ長 */
    tag_t *tag_;                                                     /* 電子タグ */
};

// 戦略にすべき
// class RingGene : public Gene {
// public:
//     int pointOfMinHamDistance( const Gene &other ) const;
// };

/*
 * =====================================================================================
 *        Class:  Life
 *  Description:  Geneを持つ生命体
 * =====================================================================================
 */
class Gene;

class Life {
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ
     *-----------------------------------------------------------------------------*/
    Life( const char *str ) { gene_ = new Gene( str ); }
    Life( int len ) { gene_ = new Gene( len ); }
    Life( Gene& gene ) { gene_ = new Gene( gene ); }
    /*-----------------------------------------------------------------------------
     *  デストラクタ
     *-----------------------------------------------------------------------------*/
    ~Life() { SAFE_DELETE( gene_ ); }
    /*-----------------------------------------------------------------------------
     *  タグ操作
     *-----------------------------------------------------------------------------*/
    Gene& getGene() const { return *gene_; }                         /* タグを返す */
    int getLen() const { return gene_->getLen(); }                   /* タグ長を返す */
    tag_t tagAt(int n) const { return gene_->tagAt(n); }             /* 特定位置のタグを返す */

    void initGene();

    void mutation( double prob=100 );
  private:
    Gene *gene_;
};

#endif
