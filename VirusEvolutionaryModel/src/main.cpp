#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "ImmuneSystem.hpp"
#include "Function.hpp"

using namespace std;


/*-----------------------------------------------------------------------------
 *  configure
 *-----------------------------------------------------------------------------*/
const int WIDTH = 30;
const int HEIGHT = WIDTH;

const int CELL_LAND_WIDTH = 30;
const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_INTERVAL = 5;
const int IMMUNE_INTERVAL = 1;
const int HUMAN_NUM = 10;


/*-----------------------------------------------------------------------------
 *
 *  宿主内の動態モデルを処理
 *
 *-----------------------------------------------------------------------------*/
void run_host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();                        /* 免疫機構を取得 */
  EACH( it_tc, IS.getTcellList() )                                   /* T細胞の移動 */
  {
    (*it_tc)->move(IS.getCellLand());
  }
  EACH( it_cell, IS.getCellLand().getCellList() ) {
    VECTOR(Cell *) neighbors = IS.getCellLand().getNeighborsAt( **it_cell );
    (*it_cell)->contact( neighbors );
  }
}
/*-----------------------------------------------------------------------------
 *
 *  エントリーポイント
 *
 *-----------------------------------------------------------------------------*/
int main()
{
  ECHO("Started Virus Evolutionary Model");
  ECHO("version 1.0");
  /*-----------------------------------------------------------------------------
   *  初期化
   *-----------------------------------------------------------------------------*/
  ECHO("Initialize");
  ECHO("Initialize Human");
  VECTOR(Human *) humans;
  FOR( i, HUMAN_NUM ) {
    humans.push_back( new Human() );
  }
  ECHO("Initialize Term");
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

  ECHO("Loop");
  while( term.loop() )
  {
    // 免疫機構
    if( term.isImmuneInterval() )
    {
      EACH( it_human, humans )
      {
        run_host_pathogen_model(**it_human);
      }
    }
    // ヒト
    if( term.isHumanInterval() )
    {
      cout << humans.size() << endl;
    }
  }

  ECHO("Finished.");
  return 0;
}
