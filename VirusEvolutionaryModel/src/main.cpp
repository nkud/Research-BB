#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "ImmuneSystem.hpp"
#include "Function.hpp"

using namespace std;

//----------------------------------------------------------------------
//  configure
//----------------------------------------------------------------------
const int TERM = 10;
const int HUMAN_INTERVAL = 2;
const int IMMUNE_INTERVAL = 1;

const int WIDTH = 10;
const int HEIGHT = WIDTH;

//const int CELL_LAND_WIDTH = 30;
//const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_NUM = 10;

//----------------------------------------------------------------------
//  宿主内の動態モデルを処理
//----------------------------------------------------------------------
void run_host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();    // 免疫機構を取得 
  /*-----------------------------------------------------------------------------
   *  T細胞の移動
   *-----------------------------------------------------------------------------*/
  EACH( it_tc, IS.getTcellList() ) {             // 各T細胞に対して
    (*it_tc)->move(IS.getCellLand());            // 移動させる
  }
  /*-----------------------------------------------------------------------------
   *  細胞の接触
   *-----------------------------------------------------------------------------*/
  EACH( it_cell, IS.getCellLand().getCellList() ) { // 各細胞に対して
    VECTOR(Cell *) neighbors = IS.getCellLand().getNeighborsAt( **it_cell ); // 近隣の細胞を取得し
    (*it_cell)->contact( neighbors );            // 接触させる
  }
  /*-----------------------------------------------------------------------------
   *  細胞の感染
   *-----------------------------------------------------------------------------*/
  EACH( it_cell, IS.getCellLand().getCellList() ) { // 各細胞に対して
    (*it_cell)->infection();                     // 感染させる
  }
  /*-----------------------------------------------------------------------------
   *  T細胞の殺傷
   *-----------------------------------------------------------------------------*/
  EACH( it_tc, IS.getTcellList() ) {             // 各T細胞に対して
    int x = (*it_tc)->getX();                    // 座標を
    int y = (*it_tc)->getY();                    // 取得して
    Cell& cell = IS.getCellLand().getCellAt(x, y); // その位置の細胞を取得して
    cell.clearInfectedViruses();                 // 感染ウイルスを除去する
  }
}

//----------------------------------------------------------------------
//  エントリーポイント
//----------------------------------------------------------------------
int main()
{
  ECHO("Started Virus Evolutionary Model");
  ECHO("version 1.0");
  //----------------------------------------------------------------------
  //  宣言・初期化
  //----------------------------------------------------------------------
  ECHO("Initialize Term");
  Term &term = Term::Instance();
  term.setMaxTerm(TERM);
  term.setHumanInterval( HUMAN_INTERVAL );
  term.setImmuneInterval( IMMUNE_INTERVAL );

  ECHO("Initialize HumanLand");
  HumanLand *humanLand = new HumanLand(WIDTH, HEIGHT); // ヒト土地を初期化
  ECHO("Initialize Human");
  VECTOR(Human *) humans;
  Human *temp;
  FOR( i, HUMAN_NUM ) {                          // 初期設定の数だけ
    temp = new Human();                          // 新しくヒトを初期化
    temp->randomLocate(*humanLand);              // ランダムに土地に配置して
    humans.push_back( temp );                    // 配列に追加していく
  }

  //----------------------------------------------------------------------
  //  計算開始
  //----------------------------------------------------------------------
  while( term.loop() )                           // 最大実行期間までループする
  {

    //----------------------------------------------------------------------
    //  宿主内動態
    //----------------------------------------------------------------------
    if( term.isImmuneInterval() ) {              // 免疫機構の実行間隔なら
      EACH( it_human, humans ) {                 // 各ヒトに対して
        run_host_pathogen_model(**it_human);     // 宿主内動態モデルを進める
      }
    }

    //----------------------------------------------------------------------
    //  ヒト
    //----------------------------------------------------------------------
    if( term.isHumanInterval() ) {               // ヒトの実行期間なら
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->move( *humanLand );         // 土地を移動させる
      }
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->contact();                  // 接触させる
      }
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->infection();                // 感染させる
      }
    }
  }
  //----------------------------------------------------------------------
  //  計算終了
  //----------------------------------------------------------------------

  ECHO("Finished.");
  return 0;
}
