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
/// @todo 戦略で実装する
class Gene
{
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ / デストラクタ
     *-----------------------------------------------------------------------------*/
    Gene( int );                                                     /* コンストラクタ: 長さ */
    Gene( int minl, int maxl );                                      /* XXX コンストラクタ: 長さ */
    Gene( const char * );                                            /* コンストラクタ: 文字列 */
    // XXX: コピーコンストラクタにする
    Gene( const Gene & gene );
    virtual ~Gene();                                                 /* デストラクタ */
    /*-----------------------------------------------------------------------------
     *  タグ操作セット
     *-----------------------------------------------------------------------------*/
    void setTagRandom();                                             /* タグをランダムに設定する */
    tag_t *getTag() const;                                           /* タグ配列へのポインタを返す */
    void setTag( const tag_t *t, int l );                            /* タグを設定 */
    int getLen() const;                                              /* タグ長を返す */
    virtual tag_t tagAt( const int ) const ;                         /* 特定の位置のタグの値を返す */
    void changeTagLenTo( int n );                                    /* タグの長さを変える */
    void printTag() const;                                           /* タグを表示 */
    // const tag_t *getTagString();

    int pointOfMinHamDistance( const Gene & ) const;                 ///< @todo 戦略で実装する 
                                                                     ///< @brief 最小ハミング距離になる位置を返す
    int flipToGeneAtPosition( const Gene &, int pos );
    int hamDistance( const Gene &, int pos ) const;

    void changeTagAtTo( int at, int num );

    void mutation();                                                 /* 突然変異を起こす */
    void mutation( double );                                         /* 突然変異を起こす */

    virtual int value();

    double valueInterval(int from, int to) { // 指定された間隔のウイルス評価値
      int ret = 0;
      to = std::max( getLen()+1, to );
      REP( i, from, to-1 ) {
        ret += std::abs( tagAt(i) - BASE_TAG );
      }
      return ret;
    }
    

    Gene& clone() const;                                             /* クローンを作成 */

  private:
    int len_;                                                        /* タグ長 */
    tag_t *tag_;                                                     /* 電子タグ */
};

class RingGene : public Gene {
 public:
  tag_t tagAt( const int n ) const;
  int pointOfMinHamDistance( const Gene &other ) const;
  int flipToGeneAtPosition( const Gene &other, int pos ) const;
};

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
    Life( Life& life ) { gene_ = new Gene( life.getGene() ); }
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
    int value() const { return getGene().value(); }
    int valueIntervale(int from, int to) const { return getGene().valueInterval(from, to); }

    Life& clone();

    void initGene();                                                 /* 遺伝子を初期化する */

    void mutation( double prob=100 );                                /* 突然変異する */
  private:
    Gene *gene_;
};

#endif
