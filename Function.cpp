#include "Function.h"
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

