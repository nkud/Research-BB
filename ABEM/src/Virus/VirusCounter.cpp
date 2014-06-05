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
bool VirusCounter :: hasDataOfVirus( const Virus& v ) {
  for(ITERATOR(Virus*) it_v=virus_data_base_.begin(); it_v!=virus_data_base_.end();)
  {
    if( v.isEqualTo((**it_v)) ) {
      return true;
    }
    it_v++;
  }
  return false;
}
/*-----------------------------------------------------------------------------
 *  pushNewVirus
 *      データベースに新しいウイルスを登録
 *-----------------------------------------------------------------------------*/
bool VirusCounter :: pushNewVirus( const Virus& v ) {
  if( hasDataOfVirus(v) ) {                                          /* データがあれば */
    return false;                                                    /* 終了 */
  } else {                                                           /* なければ */
    virus_data_base_.push_back( new Virus(v) );                     /* データを追加して */
    return true;                                                     /* 終了 */
  }
}
/*-----------------------------------------------------------------------------
 *  resetVirusDataBase
 *-----------------------------------------------------------------------------*/
void VirusCounter :: resetVirusDataBase() {
  for(ITERATOR(Virus*) it_v=virus_data_base_.begin(); it_v!=virus_data_base_.end();)
  {
//    delete (*it_v);
    it_v++;
  }
  virus_data_base_.clear();
}

int VirusCounter :: getVirusVariaty() const {
  return virus_data_base_.size();
}
ITERATOR(Virus*) VirusCounter :: getVirusDataBaseIteratorBegin() {
  return virus_data_base_.begin();
}
ITERATOR(Virus*) VirusCounter :: getVirusDataBaseIteratorEnd() {
  return virus_data_base_.end();
}
