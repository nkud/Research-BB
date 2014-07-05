/*
 * =====================================================================================
 *
       Filename:  Tag.cpp
 *
 *    Description:  タグのインターフェイス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Gene.h"
#include "Function.h"
#include "Config.h"

#include <cstring>
#include <cstdlib>

/*-----------------------------------------------------------------------------
 *
 *  コンストラクタ
 *
 *-----------------------------------------------------------------------------*/

Gene :: Gene( Gene & gene )
{
  len_ = gene.getLen();
  tag_ = new tag_t[ len_ ];
  FOR( i, len_ ) {
    tag_[i] = gene.tagAt(i);
  }
}

Gene :: Gene( int l ) :
  len_( l ),                                                         /* 指定された長さで初期化 */
  tag_( 0 )
{
  tag_ = new tag_t[ l ];                                             /* タグのメモリ領域を確保 */
  FOR( i, len_ ) {
    tag_[i] = 0;                                                     /* すべてを０で初期化 */
  }
}

Gene :: Gene( const char *str ) :
    len_( strlen( str ) ),                                           /* 文字列の長さで初期化 */
    tag_( 0 )
{
    assert( len_ > 0 );                                              /* 文字列の長さが０以下ならエラー */
    tag_ = new tag_t[ len_ ];                                        /* タグのメモリ領域を確保 */

    FOR( i, len_ ) {
        tag_[ i ] = str[ i ] - '0';                                  /* 指定された文字列で初期化 */
    }
}
///
/// value
///
int Gene :: value() {
  int ret = 0;
  FOR( i, getLen() ) {
    ret += abs( tagAt(i) - BASE_TAG );
  }
  return ret;
}

/*-----------------------------------------------------------------------------
 *  flipToGeneAtPosition
 *-----------------------------------------------------------------------------*/
int Gene :: flipToGeneAtPosition( const Gene &other, int pos )
{
  FOR( i, other.getLen() )
  {
    int mytag = tagAt(pos+i);
    int othertag = other.tagAt(i);
    if( mytag == othertag ) {
      continue;
    } else {
      if( mytag > othertag ) {
        changeTagAtTo( pos+i, mytag-1);
      } else {
        changeTagAtTo( pos+i, mytag+1);
      }
      return 0;
    }
  }
  return -1;
}

/*-----------------------------------------------------------------------------
 *  pointOfMinHamDistance
 *      ハミング距離が最小になる位置を返す
 *-----------------------------------------------------------------------------*/
int Gene :: pointOfMinHamDistance( const Gene &other ) const {
  if( getLen() < other.getLen() ) return -1;                         /* 最小値 */
  int minh = getLen();                                               /* タグを比べる位置 */
  int sp = 0;
  int tm = minh;                                                     /* 初め最小ハミング距離は最大 */
  FOR( i, getLen() )                                                 /* ずらせる回数繰り返す */
  // FOR(i, getLen()-other.getLen())
  {
//    tm = ham_distance( tag_+i, gene.getTag(), gene.getLen() );       /* ずらした位置でのハミング距離 */
    tm = hamDistance( other, i );
    if( tm <= 0 ) return -1;                                         /* (免疫獲得済み) */
    if( minh >= tm )                                                 /* の方が小さかったら */
    {
      if( minh == tm ) {                                             /* もしハミング距離が同じなら */
        if( rand_binary() ) continue;                                /* 1/2 の確率で上書きする */
      }
      minh = tm;                                                     /* 最小値を更新 */
      sp = i;                                                        /* タグの位置を記録 */
    }
  }
  if( minh <= 0 ) return -1;                                         /* 免疫獲得済み */
  return sp;                                                         /* ウイルスのタグがとりつく位置を返す */
}

// int RingGene :: pointOfMinHamDistance( const Gene &other ) const {
//   if( getLen() < other.getLen() ) return -1;                              /* 最小値 */
//   int minh = getLen();                                                   /* タグを比べる位置 */
//   int sp = 0;
//   int tm = minh;                                                     /* 初め最小ハミング距離は最大 */
//   FOR(i, getLen()-other.getLen())
//   {
//     tm = hamDistance( other, i );
//     if( tm <= 0 ) return -1;                                         /* (免疫獲得済み) */
//     if( minh >= tm )                                                 /* の方が小さかったら */
//     {
//       if( minh == tm ) {                                             /* もしハミング距離が同じなら */
//         if( rand_binary() ) continue;                                /* 1/2 の確率で上書きする */
//       }
//       minh = tm;                                                     /* 最小値を更新 */
//       sp = i;                                                        /* タグの位置を記録 */
//     }
//   }
//   if( minh <= 0 ) return -1;                                         /* 免疫獲得済み */
//   return sp;                                     /* ウイルスのタグがとりつく位置を返す */
// }

/*-----------------------------------------------------------------------------
 *  hamDistance
 *      pos から比べたハミング距離を返す
 *-----------------------------------------------------------------------------*/
int Gene :: hamDistance( const Gene &other, int pos ) const {
  int diff = 0;
  FOR(i, other.getLen()) {
    if( tagAt(i+pos) != other.tagAt(i) )
      diff++;
  }
  return diff;
}
/*-----------------------------------------------------------------------------
 *  Gene :: ~Gene()
 *-----------------------------------------------------------------------------*/
Gene :: ~Gene() {                                                    /* デストラクタ */
  assert( tag_ != NULL );
  SAFE_DELETE_ARRAY( tag_ );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Gene :: setTagRandom()
 * Description:  タグをランダムに初期化する
 *--------------------------------------------------------------------------------------
 */
void Gene :: setTagRandom() {
    assert( getLen() > 0 );
    FOR( i, getLen() )
    {
        // tag_[i] = rand_binary();                                     /* タグをランダムに初期化  */
      tag_[i] = rand_interval_int(0, T_MAX);
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Gene :: changeTagLenTo( int )
 * Description:  タグの長さを変更する
 *               変更後はすべて０で初期化
 *--------------------------------------------------------------------------------------
 */
void Gene :: changeTagLenTo( int n ) {
    len_ = n;                                                        /* 長さを再設定 */
    // delete[] tag_;                                                   /* 既存をメモリ削除 */
  SAFE_DELETE_ARRAY(tag_);
    tag_ = new tag_t[n];                                             /* 新たにメモリ割当 */
    FOR( i, n )
    {
        tag_[i] = 0;                                                 /* すべてを０で初期化 */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Gene :: getTag_()
 * Description:  タグを返す
 *--------------------------------------------------------------------------------------
 */
tag_t *Gene :: getTag() const {
    return tag_;                                                     /* タグを返す */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Gene :: getTagLen()
 * Description:  タグの長さを返す
 *----------------------------------------------------------------------------------- */
int Gene :: getLen() const {
    return len_;                                                     /* タグの長さを返す */
}

/*-----------------------------------------------------------------------------
 *  tagAt
 *      指定された位置のタグを返す
 *-----------------------------------------------------------------------------*/
tag_t Gene :: tagAt( const int n ) const {
    return tag_[ n % getLen() ];                                     /* 指定された位置のタグを返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Gene :: printTag()
 * Description:  タグを表示する
 *--------------------------------------------------------------------------------------
 */
void Gene :: printTag() const {
    std::cout << "[ " <<this<< " ]" << ": ";                         /* 自身のポインタを表示する */
    FOR( i, len_ ) {
        std::cout << tag_[i];                                        /* タグを表示する */
    }
    std::cout << std::endl;                                          /* 改行 */
}


/*-----------------------------------------------------------------------------
 *  Gene :: setTag( const tag_t *, int )
 *      タグを設定する
 *-----------------------------------------------------------------------------*/
void Gene :: setTag( const tag_t *t, int l ) {
    assert( l > 0 );                                                 /* 全長が０以下ならエラー */
    changeTagLenTo( l );                                             /* 全長を変更する */
    while( l-- ) {
        tag_[l] = t[l];                                              /* タグをコピーしていく */
    }
}


/*-----------------------------------------------------------------------------
 *  Gene :: mutation()
 *      突然変異を起こす
 *      変異は必ず起こる
 *-----------------------------------------------------------------------------*/
void Gene :: mutation() {
  int pos = rand_array( getLen() );                                  /* 配列から適当な位置を */
  if( rand_bool() ) {
    if( rand_bool() ) {
      if( tag_[pos] < T_MAX )
        tag_[pos] += 1;
    } else {
      if( tag_[pos] > 0 )
        tag_[pos] -= 1;
    }
  }
}
    // while(1) {
    //   int reduce_pos = rand_array( len_ );
    //   if( tag_[reduce_pos] > 1 ) { // 1 よりおおきければ
    //     tag_[reduce_pos] -= 1; // その位置を減らす
    //     break;
    //   }
    // }
    // return;
  // }
  // mutation(); // T_MAX ならもう一回ためす
  // tag_[ pos ] = ( tag_[ pos ] + 1 ) % T_MAX;                             /* 変更する */
// }

/*-----------------------------------------------------------------------------
 *  changeTagLenTo
 *-----------------------------------------------------------------------------*/
void Gene :: changeTagAtTo( int at, int num ) {
  tag_[ at % len_ ] = num;
}
/*-----------------------------------------------------------------------------
 *  mutation( double )
 *      突然変異を起こす
 *      確率を指定する
 *-----------------------------------------------------------------------------*/
void Gene :: mutation( double prob ) {
  if ( probability( prob ) ) {                                       /* 指定された確率で */
    mutation();
  }
}

///
/// clone()
///     @note クローン作成
///
Gene& Gene :: clone() const {
  Gene *copy = new Gene(getLen());
  FOR( i, getLen() ) {
    copy->changeTagAtTo(i, tagAt(i));
  }
  return *copy;
}
/*-----------------------------------------------------------------------------
 *
 *  Life
 *
 *-----------------------------------------------------------------------------*/
///
/// initGene()
///     @note 遺伝子初期化
///
void Life :: initGene() {
  int len = getLen();                                                /* 現在の遺伝子の長さを取得して */
  SAFE_DELETE( gene_ );                                              /* 削除 */
  gene_ = new Gene( len );                                           /* 新たに遺伝子を作成したあと */
  gene_->setTagRandom();                                             /* タグをランダムに設定 */
}

///
/// mutation()
///     @note 突然変異
///
void Life :: mutation( double prob ) {
  if( probability( prob ) ) {
    getGene().mutation( prob );
  }
}

///
/// clone()
///     @note クローン作成
///
Life& Life :: clone() {
  Life *new_life = new Life( getGene() );
  return *new_life;
}
