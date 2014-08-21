#ifndef ___FUNCTION_HPP
#define ___FUNCTION_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>

/*-----------------------------------------------------------------------------
 *  汎用マクロ
 *-----------------------------------------------------------------------------*/
#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)  /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)

#define LOG(x)              do { std::cout<< CLEAR_RIGHT << "["<<CYAN<<#x<<CLR_ST<<"]: "<<x<<std::endl; }while(0);

#define DEBUG(x)            do { std::cerr<<">>> "<<#x<<" = "<<(x)<<" (L"<<__LINE__<<")"<<" "<<__FILE__<<std::endl; }while(0);

#define ALL(a)              (a).begin(),(a).end()
#define EACH(i,c)           for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SAFE_DELETE(p)          delete p; p = NULL;
#define SAFE_DELETE_ARRAY(p)    delete[] p; p = NULL;

#define SEPARATOR           " "                                      /* 出力データを分割する文字 */

/*-----------------------------------------------------------------------------
 *  乱数用関数セット
 *-----------------------------------------------------------------------------*/
bool probability( double prob );
int uniform_int( int a, int b );
bool rand_bool();

#endif
