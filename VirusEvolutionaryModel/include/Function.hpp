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
#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)  // i: 0 ~ (m-1) 
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)

#define ASSERT(x)           do { assert(x); }while(0);
#define ECHO(x)             do { std::cout<< CLEAR_RIGHT << "----> "<<GREEN<<BOLD<<x<<STANDARD<<CLR_ST<<""<<std::endl; }while(0);
#define LOG(x)              do { log_ofs << "[ " << #x << " ] " << x << " (L"<<__LINE__<<") "<<__FILE__ << std::endl; }while(0);
#define LLOG(x)             do { std::cout<< CLEAR_RIGHT << "[ "<<GREEN<<BOLD<<#x<<STANDARD<<CLR_ST<<" ] "<<x<<std::endl; output_log(#x, x); }while(0);

#define POINT               do { static int point = 0; std::cerr<<BOLD<<RED<<"[ POINT ] "<<CLR_ST<<STANDARD<<"(L"<<__LINE__<<")"<<" "<<__FILE__<<" - "<<point++<<std::endl; }while(0);
#define DEBUG(x)            do { std::cerr<<BOLD<<"[ DEBUG ] "<<CLR_ST<<STANDARD<<#x<<": "<<BOLD<<(x)<<STANDARD<<" (L"<<__LINE__<<")" \
                            <<" "<<__FILE__<<std::endl; }while(0);

#define ALL(a)              (a).begin(),(a).end()

#if (__cplusplus == 199711)
// for c98
#define EACH(i,c)           for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#elif (__cplusplus == 201103)
// for c11
#define EACH(i,c)           for(auto i=(c).begin(); i!=(c).end(); ++i)
#endif

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SAFE_DELETE(p)          delete p; p = NULL;
#define SAFE_DELETE_ARRAY(p)    delete[] p; p = NULL;

#define SEPARATOR           " "                  // 出力データを分割する文字 
#define ENDL                std::endl
#define LOG_FNAME           "log.txt"            // ログファイル名

static std::ofstream log_ofs( LOG_FNAME, std::ios_base::out | std::ios_base::app );
/*-----------------------------------------------------------------------------
 *  乱数用関数セット
 *-----------------------------------------------------------------------------*/
int uniform_int( int a, int b );
double uniform_double( double a, double b );
bool probability( double prob );
bool rand_bool();

#endif
