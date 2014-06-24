/*
 * =====================================================================================
 *
 *       Filename:  Function.h
 *
 *    Description:  関数セット
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___FUNCTION
#define ___FUNCTION

/*-----------------------------------------------------------------------------
 *
 *  インクルードファイル
 *
 *-----------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <iostream>
#include <cassert>
/*-----------------------------------------------------------------------------
 *
 *  マクロ
 *
 *-----------------------------------------------------------------------------*/
#define FOR(i, m)           for(int (i)=0; (i)<(m); (i)++)  /* i: 0 ~ (m-1) */
#define REP(i, min, max)    for(int (i)=(min); (i)<=(max); (i)++)

#define LOG(x)              do { std::cout<<"["<<"\033[36m"<<#x<<"\033[39m"<<"]: "<<x<<std::endl; }while(0);

#define DEBUG(x)						do { std::cerr<<">>> "<<#x<<" = "<<(x)<<" (L"<<__LINE__<<")"<<" "<<__FILE__<<std::endl; }while(0);

#define TERMINAL_CLR        do { std::cout<<"\033[2J"<<std::endl; }while(0);
#define TERMINAL_LOCATION(x,y)  std::cout<<"\033["<<x<<";"<<y<<"H"<<std::endl;

#define ALL(a) 				(a).begin(),(a).end()
#define EACH(i,c) 			for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)

#define VECTOR(type)        std::vector< type >
#define ITERATOR(type)      std::vector< type >::iterator
#define C_ITERATOR(type)    std::vector< type >::const_iterator

#define SAFE_DELETE(p)			delete p; p = NULL;
#define SAFE_DELETE_ARRAY(p)	delete[] p; p = NULL;

#define SEPARATOR           " "                                      /* 出力データを分割する文字 */

/*-----------------------------------------------------------------------------
 *  タグ操作セット
 *-----------------------------------------------------------------------------*/
// int flip_once( tag_t * const, const tag_t * const, const int );      /* 一回だけフリップ */

/*-----------------------------------------------------------------------------
 *  ハミング距離関係関数セット
 *-----------------------------------------------------------------------------*/
int ham_distance( const int * const, const int * const, const int ); /* ハミング距離を計算 */
int min_ham_distance_point( const int * const, const int * const, const int, const int );                /* ハミング距離が最小になる位置を返す */

/*-----------------------------------------------------------------------------
 *  乱数用関数セット
 *-----------------------------------------------------------------------------*/
int rand_interval_int( const int, const int );                       /* 整数の幅の乱数を返す */
double rand_interval_double( const double, const double );           /* 浮動小数点の幅の乱数を返す */
int rand_array( const int );                                         /* ０から整数までの乱数を返す */
int rand_binary();                                                   /* ０か１の乱数を返す */
bool rand_bool();
int rand_sign();                                                     /* ー１か１の乱数を返す */
bool probability( double );

/*-----------------------------------------------------------------------------
 *  テンプレートセット
 *-----------------------------------------------------------------------------*/
template < typename T >                                              /* スワップ */
void SWAP( T &a, T &b ) { T t = a; a = b; b = t; }
template < typename T >                                              /* ランダム選択 */
T random_select( const T a, const T b ) { if(rand_binary() == 0) return a; else return b; }
template < typename T >                                              /* ログ出力用 */
void log(T str) { int static i=0;std::cout<<i++<<":\t"<<str<<std::endl; }

#endif
