#ifndef ___FUNCTION_HPP
#define ___FUNCTION_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

#include "Terminal.hpp"

/*-----------------------------------------------------------------------------
 *  汎用マクロ
 *-----------------------------------------------------------------------------*/
#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)  /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)

#define ECHO(x)             do { std::cout<< CLEAR_RIGHT << "----> "<<GREEN<<BOLD<<x<<STANDARD<<CLR_ST<<""<<std::endl; }while(0);
#define LOG(x)              do { output_log(#x, x); }while(0);
#define LLOG(x)             do { std::cout<< CLEAR_RIGHT << "[ "<<GREEN<<BOLD<<#x<<STANDARD<<CLR_ST<<" ] "<<x<<std::endl; output_log(#x, x); }while(0);
static int point = 0;
#define POINT               do { std::cerr<<BOLD<<RED<<"[ POINT ] "<<CLR_ST<<STANDARD<<"(L"<<__LINE__<<")"<<" "<<__FILE__<<" - "<<point++<<std::endl; }while(0);
#define DEBUG(x)            do { std::cerr<<BOLD<<"[ DEBUG ] "<<CLR_ST<<STANDARD<<#x<<": "<<BOLD<<(x)<<STANDARD<<" (L"<<__LINE__<<")" \
                            <<" "<<__FILE__<<std::endl; }while(0);

#define ALL(a)              (a).begin(),(a).end()
#define EACH(i,c)           for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SAFE_DELETE(p)          delete p; p = NULL;
#define SAFE_DELETE_ARRAY(p)    delete[] p; p = NULL;

#define SEPARATOR           " "                                      /* 出力データを分割する文字 */
#define LOG_FNAME           "log"

static std::ofstream ofs(LOG_FNAME, std::ios_base::out | std::ios_base::app);
template < typename T >
void output_log( const char *title, T value )
{
  ofs << "[ " << title << " ] " << value << " (L"<<__LINE__<<") "<<__FILE__ << std::endl;
}
/*-----------------------------------------------------------------------------
 *  乱数用関数セット
 *-----------------------------------------------------------------------------*/
int uniform_int( int a, int b );
double uniform_double( double a, double b );
bool probability( double prob );
bool rand_bool();

#endif
