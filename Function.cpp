/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ham_distance
 *  Description:  ハミング距離を求める。
 *                同じ長さ限定。
 * =====================================================================================
 */
#include "Global.h"
#include <cstdlib>
#include <algorithm>

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
 *  Description:  
 * =====================================================================================
 */
int min_ham_distance(int *a, int *b, int an, int bn)
{
    int n = abs(an - bn) + 1;
    int m = an;                                 // 最小値

    FOR(i, n)
    {
        m = std::min( m, ham_distance( a+i, b, bn ) );
    }
    return m;
}
