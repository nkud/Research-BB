#include <iostream>

#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "ImmuneSystem.hpp"
#include "Function.hpp"

using namespace std;

// configure
const int WIDTH = 30;
const int HEIGHT = WIDTH;

const int CELL_LAND_WIDTH = 30;
const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_INTERVAL = 5;
const int IMMUNE_INTERVAL = 1;
const int HUMAN_NUM = 10;
// ---------

// 宿主内動態モデルの処理
void host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();                        /* 免疫機構を取得 */
  EACH( it_tc, IS.getTcellList() )                                   /* T細胞の移動 */
  {
    (*it_tc)->move(IS.getCellLand());
    DEBUG( (*it_tc)->getX() );
  }
  EACH( it_cell, IS.getCellLand().getCellList() ) {
    (*it_cell)->contact( IS.getCellLand().getNeighborsAt(**it_cell) );
  }
}

int main()
{
  // 初期化
  VECTOR(Human *) humans;
  FOR( i, HUMAN_NUM ) {
    humans.push_back( new Human() );
  }
  Term &term = Term::Instance();
  term.setMaxTerm(20);
  term.setHumanInterval( HUMAN_INTERVAL );
  term.setImmuneInterval( IMMUNE_INTERVAL );
  HumanLand* humanLand = new HumanLand(WIDTH, HEIGHT);

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
      EACH( it_human, humans )
      {
        host_pathogen_model(**it_human);
      }
    }
    // ヒト
    if( term.isHumanInterval() )
    {
      cout << "Human Interval" << endl;
      cout << humans.size() << endl;
    }
  }

  cout << "Finished." << endl;
  return 0;
}
