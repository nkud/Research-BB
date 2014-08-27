#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"
#include "FileFactory.hpp"
#include "Benchmark.hpp"

using namespace std;

/// @todo __Host Class: ウイルスに感染する可能性のあるエージェント。免疫機構を持つ.Cell, Human

//----------------------------------------------------------------------
//  configure
//----------------------------------------------------------------------
const int TERM = 1000;
const int HUMAN_INTERVAL = 2;
const int IMMUNE_INTERVAL = 1;

const int WIDTH = 50;
const int HEIGHT = WIDTH;

const int TCELL_MINIMUM_SIZE = 10;
const int TCELL_LIFESPAN = 8;

//const int CELL_LAND_WIDTH = 30;
//const int CELL_LAND_HEIGHT = CELL_LAND_WIDTH;

const int HUMAN_NUM = 1;


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
  ECHO(__cplusplus);
  //----------------------------------------------------------------------
  //  宣言・初期化
  //----------------------------------------------------------------------
  ECHO("期間初期化");
  Term &term = Term::Instance();
  term.setMaxTerm(TERM);                         // 最大実行期間を設定

  ECHO("ヒト土地初期化");
  HumanLand *humanLand = new HumanLand(WIDTH, HEIGHT); // ヒト土地を初期化

  ECHO("ヒト初期化");
  VECTOR(Human *) humans;
  Human *temp;
  FOR( i, HUMAN_NUM ) {                          // 初期設定の数だけ
    temp = new Human( 10, new CellLand(WIDTH, HEIGHT) );                      // 新しくヒトを初期化
    temp->randomLocate(*humanLand);              // ランダムに土地に配置して
    humans.push_back( temp );                    // 配列に追加していく
  }

  Virus *virus = new Virus( 10 );                // 新しいウイルスを初期化
  humans[0]->getCellLand().getCellAt(0,0).pushNewVirusCloneToInfectedVirusList(*virus);
  //----------------------------------------------------------------------
  //  計算開始
  //----------------------------------------------------------------------
  Benchmark::Instance().startTimer();
  ECHO("計算開始");
  while( term.loop() )                           // 最大実行期間までループする
  {
    if(term.isInterval(1000)) ECHO(term.getTerm()); // 途中経過をログ
    // デバッグログ ------------------------------------------------------
    LOG( term.getTerm() );
    LOG( humans[0]->getCellLand().calcInfectedCellDensity() );
    output_value_with_term("dense.txt", humans[0]->getCellLand().calcInfectedCellDensity() );

    //----------------------------------------------------------------------
    //  宿主内の動態を処理
    //----------------------------------------------------------------------
    if( term.isInterval(IMMUNE_INTERVAL) )       // 免疫機構の実行期間なら
    {
      EACH( it_human, humans ) {                 // 各ヒトに対して
        run_host_pathogen_model( **it_human );   // 宿主内動態モデルを進める
                                                 // （最下部に実装あり）
      }
    }

    //----------------------------------------------------------------------
    //  ヒト集団の処理
    //----------------------------------------------------------------------
    if( term.isInterval(HUMAN_INTERVAL) )        // ヒトの実行期間なら
    {
      #ifdef HUMAN_PROCESS
      LOG("ヒトの移動")
      humanLand->clearMap();                     // 土地の登録をクリア
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->move( *humanLand );         // 移動させて
        humanLand->resistHuman(**it_human);      // 土地に登録する
      }
      LOG("ヒトの接触")
      EACH( it_human, humans ) {                 // 各ヒトに対して
        VECTOR(Human *) neighbors = humanLand->getNeighborsAt( **it_human );
        EACH( it_neighbor, neighbors ) {
          (*it_human)->contact( **it_neighbor ); // 接触させる
        }
      }
      LOG("ヒトの感染")
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->infection();                // 感染させる
      }
#endif
    }
    output_value_with_term("test.txt", humans[0]->getTcellList().size() );
  }
  //----------------------------------------------------------------------
  //  計算終了
  //----------------------------------------------------------------------
  ECHO("計算終了");
  Benchmark::Instance().stopTimer();
  LOG( Benchmark::Instance().getTime() );
  return 0;
}

//----------------------------------------------------------------------
//
//  宿主内の動態を処理
//
//----------------------------------------------------------------------
void run_host_pathogen_model( Human& human )
{
  CellLand& cell_land = human.getCellLand();        // 細胞土地を取得
  VECTOR(Cell *)& cell_list = cell_land.getCellList(); // 細胞リストを取得
  VECTOR(Tcell *)& tcell_list = human.getTcellList(); // T細胞リストを取得
  //----------------------------------------------------------------------
  //  T細胞の移動
  //----------------------------------------------------------------------
  LOG("T細胞の移動")
  EACH( it_tc, tcell_list ) {                    // 各T細胞に対して
    (*it_tc)->move(cell_land);                   // 移動させる
  }
  //----------------------------------------------------------------------
  //  細胞の接触
  //----------------------------------------------------------------------
  LOG("細胞の接触")
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    VECTOR(Cell *) neighbors = cell_land.getNeighborsAt( **it_cell ); // 近隣の細胞を取得し
    EACH( it_neighbor, neighbors ) {
      (*it_cell)->contact( **it_neighbor );            // 接触させる
    }
  }
  //----------------------------------------------------------------------
  //  細胞の感染
  //----------------------------------------------------------------------
  LOG("細胞の感染")
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    (*it_cell)->infection();                     // 感染させる
  }
  //----------------------------------------------------------------------
  //  T細胞の殺傷
  //----------------------------------------------------------------------
  LOG("T細胞の殺傷")
  VECTOR(Tcell *) new_tcell;
  EACH( it_tc, tcell_list ) {                    // 各T細胞に対して
    int x = (*it_tc)->getX();                    // 座標を
    int y = (*it_tc)->getY();                    // 取得して
    Cell& cell = cell_land.getCellAt(x, y);      // その位置の細胞を取得して
    if( cell.isInfected() ) {                    // 細胞が感染していれば
      cell.clearInfectedViruses();               // ウイルスを除去して
      new_tcell.push_back( &( (*it_tc)->clone() ) ); // T細胞を増やす
    }
  }
  LOG("新しいT細胞を追加")
  LOG( new_tcell.size() );
  LOG( tcell_list.size() );
  EACH( it_tcell, new_tcell ) {                  // 新しいT細胞を
    tcell_list.push_back( *it_tcell );           // 追加する
  }

  //----------------------------------------------------------------------
  //  T細胞の寿命
  //----------------------------------------------------------------------
  for(ITERATOR(Tcell *)it=tcell_list.begin(); it!=tcell_list.end(); ) {
    (*it)->aging();
    if (human.enoughNumberOfTcellToRemove( TCELL_MINIMUM_SIZE )) {
      if ((*it)->willDie( TCELL_LIFESPAN )) {
        human.eraseTcell( it );
      } else {
        it++;
      }
    } else {
      it++;
    }
  }
  // EACH( it_tcell, tcell_list ) {                 // 各T細胞に対して
  //   (*it_tcell)->aging();
  //   if( human.enoughNumberOfTcellToRemove(10) ) { // ヒトが十分T細胞を所持していれば
  //     if( (*it_tcell)->willDie( 0 ) ) {          // T細胞が寿命のとき
  //       human.eraseTcell( it_tcell );            // T細胞を削除
  //     }
  //   }
  // }
  output_value_with_term("tcell-size.txt", tcell_list.size() );
}
