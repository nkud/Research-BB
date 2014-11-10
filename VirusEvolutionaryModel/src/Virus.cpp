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

int Virus :: getInfectionRateForCell( Cell& cell ) {
  // 100 - 細胞にとのハミング距離
  int rate = 100 - getFitnessRateForCell( cell );
  return rate;
}

int Virus :: getMutationRate() {
  return V_MUTATION_RATE;
}

int Virus :: getFitnessRateForCell( Cell& cell ) {
  int rate = 0;
  // int ham_dis = minimumHammingDistanceFor( cell.getGene() );
  int ham_dis = value();                         // つまり遺伝子コードの重み
  rate = (double)ham_dis / getLen() * 100;

  return rate;
}
