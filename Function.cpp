#include "Function.h"
#include <cstdlib>
#include <algorithm>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_once
 *  Description:  
 * =====================================================================================
 */
int flip_once( tag_t *a, tag_t *b, int len )    /* 一回だけフリップ */
{
    FOR( i, len )                               /* タグの長さだけ繰り返す */
    {
        if( *(a+i) == *(b+i) )
        {
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
 *  Description:  
 * =====================================================================================
 */
int ham_distance(int *a, int *b, int n)
{
    int diff = 0;

    FOR(i, n)
    {
        if( a[i] != b[i] )
            diff++;
    }
    return diff;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  min_ham_distance
 *  Description:  最小ハミング距離が 0（なし）-> return -1
 *                最小ハミング距離が n        -> return  n
 * =====================================================================================
 */
int min_ham_distance(int *a, int *v, int an, int vn) /* XXX: a > b だけ想定している */
{
    int min = an;                               /* 最小値 */
    int sp = 0;                                 /* タグを比べる位置 */

    int tm = min;
    FOR( i, an-vn+1 )
    {
        tm = ham_distance( a+i, v, vn );
        if( min > tm )
        {
            min = tm;                           /* 最小値を更新 */
            sp = i;                             /* タグの位置を記録 */
        }
    }
    if( min <= 0 ) return -1;                   /* 免疫獲得済み */
    return sp;                                  /* ウイルスのタグがとりつく位置を返す */
}


/*-----------------------------------------------------------------------------
 *  RANDOMIZE SET
 *-----------------------------------------------------------------------------*/
int rand_interval_int(int min, int max)
{
    return (int)( rand() * (max + min + 1.0) / (1.0 + RAND_MAX) );
}

double rand_interval_double(double min, double max)
{
    return (double)( rand() * (max + min + 1.0) / (1.0 + RAND_MAX) );
}

int rand_array( int n ) {
    return rand() % n;
}

int rand_binary()
{
    int ret;

    ret = rand() % 2;

    return ret;
}

int rand_sign()
{
    int ret;

    ret = rand()%2 ? 1 : -1;

    return ret;
}

