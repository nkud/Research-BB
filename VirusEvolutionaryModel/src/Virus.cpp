#include "Virus.hpp"
#include "Config.hpp"

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

int Virus :: getMutationRate() {
  return V_MUTATION_RATE;
}
