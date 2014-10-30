#include "Virus.hpp"
#include "Config.hpp"
#include "Cell.hpp"

//--------------------------------------------------------------------------------------
//       Class:  Virus
//      Method:  clone
// Description:  クローンを作成する
//--------------------------------------------------------------------------------------
Virus *Virus :: clone()
{
  Virus *newv = new Virus( getCString() );       // タグから初期化
  newv->mutation( getMutationRate() );           // 突然変異させる
  return newv;
}

// int Virus :: getInfectionRate() {
//   return V_INF_RATE;
// }

int Virus :: getInfectionRateForCell( Cell& cell ) {
  int rate = 100 - getAdaptationRateForCell( cell );
  return rate;
}

int Virus :: getMutationRate() {
  return V_MUTATION_RATE;
}

int Virus :: getAdaptationRateForCell( Cell& cell ) {
  int rate = 0;
  // int ham_dis = minimumHammingDistanceFor( cell.getGene() );
  int ham_dis = value();
  rate = (double)ham_dis / getLen() * 100;

  return rate;
}
