#include "Function.h"
#include <cstdlib>
#include <algorithm>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_once
 *  Description:  
 * =====================================================================================
 */
int flip_once( tag_t *a, tag_t *b, const int len )    /* 一回だけフリップ */
{
    FOR( i, len )                               /* タグの長さだけ繰り返す */
    {
        if( *(a+i) == *(b+i) ) {
            continue;                           /* 同じなら次に移動 */
        }
        else                                    /* 違ったら */
        {
            *(a+i) = *(b+i);                    /* ひとつタグをフリップ */
            return 0;                           /* 終了 */
        }
    }
    return -1;                                  /* 同じタグだった */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ham_distance( int *, int *, int )
 *  Description:  ハミング距離を返す
 * =====================================================================================
 */
int ham_distance(const int *a, const int *b, const int n) {
    int diff = 0;
    FOR(i, n) {
        if( a[i] != b[i] )
            diff++;
    }
    return diff;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  min_ham_distance
 *  Description:  最小ハミング距離が 0（なし）-> return -1
 *                最小ハミング距離が n（ >0 ）-> return sp（タグの位置）
 * =====================================================================================
 */                                             /* XXX: 名前を変える */
int min_ham_distance(int *a, int *v, int an, int vn) /* XXX: a > b だけ想定している */
{
    int minh = an;                              /* 最小値 */
    int sp = 0;                                 /* タグを比べる位置 */

    int tm = minh;                              /* 初め最小ハミング距離は最大 */
    FOR( i, an-vn+1 )                           /* ずらせる回数繰り返す */
    {
        tm = ham_distance( a+i, v, vn );        /* ずらした位置でのハミング距離 */
        if( tm <= 0 ) return -1;                /* (免疫獲得済み) */
        if( minh >= tm )                        /* の方が小さかったら */ /* XXX: あってる？ */
        {
            if( minh == tm ) {                  /* もしハミング距離が同じなら */
                if( rand_binary() ) continue;   /* 1/2 の確率で上書きする */
            }
            minh = tm;                          /* 最小値を更新 */
            sp = i;                             /* タグの位置を記録 */
        }
    }
    if( minh <= 0 ) return -1;                  /* 免疫獲得済み */
    return sp;                                  /* ウイルスのタグがとりつく位置を返す */
}


/*-----------------------------------------------------------------------------
 *  RANDOMIZE SET
 *-----------------------------------------------------------------------------*/
int rand_interval_int(int min, int max) {
    return min + (int)( rand() * (max - min + 1.0) / (1.0 + RAND_MAX) );
}

double rand_interval_double(double min, double max) {
    return min + (double)( rand() * (max - min) / (1.0 + RAND_MAX) ); /* XXX: これでいいか？ */
}

int rand_array( int n ) {
    return rand() % n;
}

int rand_binary() {
    int ret;

    ret = rand() % 2;

    return ret;
}

int rand_sign() {
    int ret;

    ret = rand()%2 ? 1 : -1;

    return ret;
}

