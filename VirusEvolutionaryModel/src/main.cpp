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
const int TERM = 30;
const int HUMAN_INTERVAL = 5;
const int IMMUNE_INTERVAL = 1;

const int WIDTH = 30;
const int HEIGHT = WIDTH;

//const int CELL_LAND_WIDTH = 30;
//const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_NUM = 10;


/*-----------------------------------------------------------------------------
 *
 *  宿主内の動態モデルを処理
 *
 *-----------------------------------------------------------------------------*/
void run_host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();                        /* 免疫機構を取得 */

  /*-----------------------------------------------------------------------------
   *  T細胞の移動
   *-----------------------------------------------------------------------------*/
  EACH( it_tc, IS.getTcellList() )
  {
    (*it_tc)->move(IS.getCellLand());
  }
  /*-----------------------------------------------------------------------------
   *  細胞の接触
   *-----------------------------------------------------------------------------*/
  EACH( it_cell, IS.getCellLand().getCellList() ) {
    VECTOR(Cell *) neighbors = IS.getCellLand().getNeighborsAt( **it_cell );
    (*it_cell)->contact( neighbors );
  }
  /*-----------------------------------------------------------------------------
   *  細胞の感染
   *-----------------------------------------------------------------------------*/
  EACH( it_cell, IS.getCellLand().getCellList() ) {
    (*it_cell)->infection();
    (*it_cell)->getInfectedVirusListSize();
  }
  /*-----------------------------------------------------------------------------
   *  T細胞の殺傷
   *-----------------------------------------------------------------------------*/
  EACH( it_tc, IS.getTcellList() )
  {
    int x = (*it_tc)->getX();
    int y = (*it_tc)->getY();
    Cell& cell = IS.getCellLand().getCellAt(x, y);
    cell.clearInfectedViruses();
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
  ECHO("Initialize Term");
  Term &term = Term::Instance();
  term.setMaxTerm(TERM);
  term.setHumanInterval( HUMAN_INTERVAL );
  term.setImmuneInterval( IMMUNE_INTERVAL );

  ECHO("Initialize Human");
  VECTOR(Human *) humans;
  FOR( i, HUMAN_NUM ) {
    humans.push_back( new Human() );
  }
  ECHO("Initialize HumanLand");
  HumanLand *humanLand = new HumanLand(WIDTH, HEIGHT);

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
      /*-----------------------------------------------------------------------------
       *  移動
       *-----------------------------------------------------------------------------*/
      EACH( it_human, humans ) {
        (*it_human)->move( *humanLand );
      }
      /*-----------------------------------------------------------------------------
       *  接触
       *-----------------------------------------------------------------------------*/
      EACH( it_human, humans ) {
        (*it_human)->contact();
      }
      /*-----------------------------------------------------------------------------
       *  感染
       *-----------------------------------------------------------------------------*/
      EACH( it_human, humans ) {
        (*it_human)->infection();
      }
    }
  }

  ECHO("Finished.");
  return 0;
}
