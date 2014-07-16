/*
 * =====================================================================================
 *
 *       Filename:  VirusCounter.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU
 *
 * =====================================================================================
 */

#include "VirusCounter.h"
#include "Virus.h"
#include "Config.h"
#include "Function.h"

double VirusCounter :: calcAveValue() {
  double sum = 0;
  double ave = 0;
  EACH( it_v, virus_data_base_ ) {
    sum += (**it_v).value();
  }
  if( sum == 0 ) return 0;
  ave = (double)sum/(double)getVirusVariaty();
  return ave;
}

/*-----------------------------------------------------------------------------
 *  Instance()
 *-----------------------------------------------------------------------------*/
VirusCounter& VirusCounter :: Instance() {
    static VirusCounter singleton;
    return singleton;                                                /* インスタンスを返す */
}
/*-----------------------------------------------------------------------------
 *  VirusCounter()
 *-----------------------------------------------------------------------------*/
VirusCounter :: VirusCounter() {
  LOG( "init VirusCounter" );
  count_mutation_ = 0;
  // virus_data_base_ = new VECTOR( Virus* );
}
/*-----------------------------------------------------------------------------
 *  reset()
 *-----------------------------------------------------------------------------*/
void VirusCounter :: reset() {
  resetCountMutation();
  resetVirusDataBase();
  resetVirusNumberDataBase();
}

/*-----------------------------------------------------------------------------
 *
 *  突然変異回数
 *
 *-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *  countUpMutation()
 *-----------------------------------------------------------------------------*/
int VirusCounter :: countUpMutation() {
  count_mutation_++;
  return count_mutation_;
}

/*-----------------------------------------------------------------------------
 *
 *  ウイルスの種類
 *
 *-----------------------------------------------------------------------------*/
int VirusCounter :: hasDataOfVirus( const __VirusInterface& v ) {
  int n = 0;
  EACH( it_v, getVirusDataBase() )
  {
    if( v.isEqualTo((**it_v)) ) {
      assert( v == (**it_v) and "同じウイルス" );
      return n;
    }
    n++;
  }
  return -1;
}
/*-----------------------------------------------------------------------------
 *  pushNewVirus
 *      データベースに新しいウイルスを登録
 *-----------------------------------------------------------------------------*/
bool VirusCounter :: pushNewVirus( __VirusInterface& v ) {
  int f = hasDataOfVirus(v);
  if( f != -1 ) {                                          /* データがあれば */
    virus_number_data_base_[f]++;
    return false;                                                    /* 終了 */
  } else {                                                           /* なければ */
//    virus_data_base_.push_back( new __VirusInterface( v ) );                     /* データを追加して */
    /// @todo ウイルスのクローンについて要検証
    virus_data_base_.push_back( &v.clone() );                     /* データを追加して */
    virus_number_data_base_.push_back( 1 );
    return true;                                                     /* 終了 */
  }
}
/*-----------------------------------------------------------------------------
 *  resetVirusDataBase
 *-----------------------------------------------------------------------------*/
void VirusCounter :: resetVirusDataBase() {
  EACH( it_v, getVirusDataBase() ) {
    SAFE_DELETE( *it_v );
  }
  virus_data_base_.clear();
}

int VirusCounter :: getVirusVariaty() const {
  return virus_data_base_.size();
}
ITERATOR(__VirusInterface*) VirusCounter :: getVirusDataBaseIteratorBegin() {
  return virus_data_base_.begin();
}
ITERATOR(__VirusInterface*) VirusCounter :: getVirusDataBaseIteratorEnd() {
  return virus_data_base_.end();
}
