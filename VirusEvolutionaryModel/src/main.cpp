#include <iostream>

#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "ImmuneSystem.hpp"
#include "Function.hpp"

using namespace std;

// configure
const int WIDTH = 30;
const int HUMAN_INTERVAL = 5;
const int IMMUNE_INTERVAL = 1;

const int HUMAN_NUM = 10;
// ---------

// 宿主内動態モデルの処理
void host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();                        // 免疫機構を取得 
  EACH( it_cell, IS.getCellLand().getCellList() ) {
    cout << (*it_cell)->isInfected() << endl;
  }
}

int main()
{
  cout << "Virus Evolutionary Model" << endl;
  cout << "version 1.0" << endl;

  // 初期化
  VECTOR(Human *) human;
  FOR( i, HUMAN_NUM ) {
    human.push_back( new Human() );
  }
  Term &term = Term::Instance();
  term.setMaxTerm(20);
  term.setHumanInterval( HUMAN_INTERVAL );
  term.setImmuneInterval( IMMUNE_INTERVAL );
//  HumanLand* humanLand = new HumanLand(WIDTH, WIDTH);

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
      cout << human.size() << endl;
    }
  }

  cout << "Finished." << endl;
  return 0;
}
