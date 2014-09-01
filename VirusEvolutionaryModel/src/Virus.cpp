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
  return newv;
}

int Virus :: getInfectionRate() {
  return V_INF_RATE;
}
