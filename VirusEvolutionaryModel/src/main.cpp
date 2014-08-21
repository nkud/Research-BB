#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "ImmuneSystem.hpp"
#include "Function.hpp"

using namespace std;

/// @todo __Host Class: ウイルスに感染する可能性のあるエージェント。免疫機構を持つ.Cell, Human

//----------------------------------------------------------------------
//  configure
//----------------------------------------------------------------------
const int TERM = 10;
const int HUMAN_INTERVAL = 2;
const int IMMUNE_INTERVAL = 1;

const int WIDTH = 20;
const int HEIGHT = WIDTH;

//const int CELL_LAND_WIDTH = 30;
//const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_NUM = 20;


//----------------------------------------------------------------------
//  宿主内動態モデルの宣言（ main関数より下に実装あり ）
//----------------------------------------------------------------------
void run_host_pathogen_model( Human& human );

//----------------------------------------------------------------------
//
//  エントリーポイント
//
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
  term.setMaxTerm(TERM);                         // 最大実行期間を設定
  term.setHumanInterval( HUMAN_INTERVAL );       // ヒト実行間隔を設定
  term.setImmuneInterval( IMMUNE_INTERVAL );     // 免疫実行間隔を設定

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

  Virus *virus = new Virus();
  humans[0]->getImmuneSystem().getCellLand().getCellAt(0,0).pushNewVirusToInfectedVirusList(*virus);
  //----------------------------------------------------------------------
  //  計算開始
  //----------------------------------------------------------------------
  while( term.loop() )                           // 最大実行期間までループする
  {
    DEBUG( term.getTerm() );
    //----------------------------------------------------------------------
    //  宿主内の動態を処理
    //----------------------------------------------------------------------
    if( term.isImmuneInterval() )                // 免疫機構の実行期間なら
    {
      EACH( it_human, humans ) {                 // 各ヒトに対して
        run_host_pathogen_model( **it_human );   // 宿主内動態モデルを進める
                                                 // （最下部に実装あり）
      }
    }

    //----------------------------------------------------------------------
    //  ヒト集団の処理
    //----------------------------------------------------------------------
    if( term.isHumanInterval() )                 // ヒトの実行期間なら
    {
      humanLand->clearMap();                     // 土地の登録をクリア
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->move( *humanLand );         // 移動させて
        humanLand->resistHuman(**it_human);      // 土地に登録する
      }
      EACH( it_human, humans ) {                 // 各ヒトに対して
        VECTOR(Human *) neighbors = humanLand->getNeighborsAt( **it_human );
        (*it_human)->contact( neighbors );      // 接触させる
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

//----------------------------------------------------------------------
//
//  宿主内の動態を処理
//
//----------------------------------------------------------------------
void run_host_pathogen_model( Human& human )
{
  ImmuneSystem& IS = human.getImmuneSystem();    // 免疫機構を取得 
  //----------------------------------------------------------------------
  //  T細胞の移動
  //----------------------------------------------------------------------
  EACH( it_tc, IS.getTcellList() ) {             // 各T細胞に対して
    (*it_tc)->move(IS.getCellLand());            // 移動させる
  }
  //----------------------------------------------------------------------
  //  細胞の接触
  //----------------------------------------------------------------------
  EACH( it_cell, IS.getCellLand().getCellList() ) { // 各細胞に対して
    VECTOR(Cell *) neighbors = IS.getCellLand().getNeighborsAt( **it_cell ); // 近隣の細胞を取得し
    (*it_cell)->contact( neighbors );            // 接触させる
  }
  //----------------------------------------------------------------------
  //  細胞の感染
  //----------------------------------------------------------------------
  EACH( it_cell, IS.getCellLand().getCellList() ) { // 各細胞に対して
    (*it_cell)->infection();                     // 感染させる
  }
  //----------------------------------------------------------------------
  //  T細胞の殺傷
  //----------------------------------------------------------------------
  EACH( it_tc, IS.getTcellList() ) {             // 各T細胞に対して
    int x = (*it_tc)->getX();                    // 座標を
    int y = (*it_tc)->getY();                    // 取得して
    Cell& cell = IS.getCellLand().getCellAt(x, y); // その位置の細胞を取得して
    cell.clearInfectedViruses();                 // 感染ウイルスを除去する
  }
}
