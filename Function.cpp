#include "Function.h"
#include <cstdlib>
#include <algorithm>


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
int min_ham_distance(int *a, int *b, int an, int bn) /* XXX: a > b だけ想定している */
{
    int m = an;                                 /* 最小値 */
    int sp = 0;                                 /* タグを比べる位置。少しずつずらす */

    FOR( sp, bn+sp <= an )
    {
        m = std::min( m, ham_distance( a+i, b, bn ) ); /* ハミング距離の最小値を更新 */
    }

    if( m == an ) return -1;                    /* 免疫獲得済み */
    else return sp;                             /* ウイルスのタグがとりつく位置を返す */
}

int rand_interval_int(int min, int max)
{
    return (int)( rand() * (max + min + 1.0) / (1.0 + RAND_MAX) );
}

double rand_interval_double(double min, double max)
{
    return (double)( rand() * (max + min + 1.0) / (1.0 + RAND_MAX) );
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

