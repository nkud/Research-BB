#include <iostream>

#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "ImmuneSystem.hpp"

using namespace std;

// configure
const int WIDTH = 30;
const int HUMAN_INTERVAL = 5;
const int IMMUNE_INTERVAL = 1;
// ---------

void host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();
}

int main()
{
  cout << "Virus Evolutionary Model" << endl;

  // 初期化
  Term &term = Term::Instance();
  term.setMaxTerm(20);
  term.setHumanInterval( HUMAN_INTERVAL );
  term.setImmuneInterval( IMMUNE_INTERVAL );
  HumanLand* humanLand = new HumanLand(WIDTH, WIDTH);
  CellLand* cellLand = new CellLand(WIDTH, WIDTH);

  // ウイルスの増殖
  // T細胞の移動
  // T細胞のウイルス殺傷
  // T細胞の寿命
  // T細胞を補完する

  while( term.loop() )
  {
    cout << term.getTerm() << endl;
    // 免疫機構
    if( term.isImmuneInterval() )
    {
      cout << "Immune Interval" << endl;
    }
    // ヒト
    if( term.isHumanInterval() )
    {
      cout << "Human Interval" << endl;
    }
  }

  return 0;
}
