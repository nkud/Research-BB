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

int Virus :: getInfectionRate() {
  return V_INF_RATE;
}

int Virus :: getInfectionRate( Cell& cell ) {
  return getAdaptationRateForCell( cell );
}

int Virus :: getMutationRate() {
  return V_MUTATION_RATE;
}

int Virus :: getAdaptationRateForCell( Cell& cell ) {
  int rate = 0;
  int ham_dis = minimumHammingDistanceFor( cell.getGene() );
  rate = ham_dis / getLen() * 100;
  return rate;
}
