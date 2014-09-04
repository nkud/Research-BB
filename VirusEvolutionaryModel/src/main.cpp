#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"
#include "Random.hpp"
#include "FileFactory.hpp"
#include "Benchmark.hpp"

#include "Config.hpp"

using namespace std;

#define HUMAN_SYSTEM
#define IMMUNE_SYSTEM

/// @todo __Host Class: ウイルスに感染する可能性のあるエージェント。免疫機構を持つ.Cell, Human

//----------------------------------------------------------------------
//  宿主内動態モデルの宣言（ main関数より下に実装あり ）
//----------------------------------------------------------------------
void run_host_pathogen_model( Human& human );

//----------------------------------------------------------------------
//
//  エントリーポイント
//
//----------------------------------------------------------------------
int
main()
{
  Random::Instance().setRandomStrategy( new __MersenneTwister ); // 乱数生成器をメルセンヌに設定
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
  HumanLand *humanLand = new HumanLand(HUMAN_LAND_WIDTH, HUMAN_LAND_HEIGHT); // ヒト土地を初期化

  ECHO("ヒト初期化");
  VECTOR(Human *) humans;
  Human *h;
  FOR( i, HUMAN_SIZE ) {                          // 初期設定の数だけ
    h = new Human( TCELL_LEN,
      TCELL_MINIMUM_SIZE,
      new CellLand(CELL_LAND_WIDTH, CELL_LAND_HEIGHT) 
      ); // 新しくヒトを初期化
    h->randomLocate(*humanLand);              // ランダムに土地に配置して
    humans.push_back( h );                    // 配列に追加していく
  }

  Virus *virus = new Virus( V_TAG );             // 新しいウイルスを初期化
  humans[0]->getCellLand().getCellAt(0,0).pushNewVirusCloneToInfectedVirusList(*virus);
  //----------------------------------------------------------------------
  //  計算開始
  //----------------------------------------------------------------------
  Benchmark::Instance().startTimer();
  ECHO("計算開始");
  while( term.loop() )                           // 最大実行期間までループする
  {
    if(term.isInterval(100)) {                   // 途中経過を表示
      ECHO( term.getTerm() << ", " << term.calcEstimatedRemainingTime());
    }
    //----------------------------------------------------------------------
    //  宿主内の動態を処理
    //----------------------------------------------------------------------
#ifdef IMMUNE_SYSTEM
    if( term.isInterval(IMMUNE_INTERVAL) )       // 免疫機構の実行期間なら
    {
      EACH( it_human, humans ) {                 // 各ヒトに対して
        run_host_pathogen_model( **it_human );   // 宿主内動態モデルを進める
                                                 // （最下部に実装あり）
      }
    }
#endif
    //----------------------------------------------------------------------
    //  ヒト集団の処理
    //----------------------------------------------------------------------
#ifdef HUMAN_SYSTEM
    if( term.isInterval(HUMAN_INTERVAL) )        // ヒトの実行期間なら
    {
      // ヒトの移動
      humanLand->clearMap();                     // 土地の登録をクリア
      EACH( it_human, humans ) {                 // 各ヒトに対して
        // XXX: 症候性機関でなければ
        (*it_human)->move( *humanLand );         // 移動させて
        humanLand->resistHuman(**it_human);      // 土地に登録する
      }
      // ヒトの接触
      EACH( it_human, humans ) {                 // 各ヒトに対して
        VECTOR(Human *) neighbors = humanLand->getNeighborsAt( **it_human );
        EACH( it_neighbor, neighbors ) {
          (*it_human)->contact( **it_neighbor ); // 接触させる
        }
      }
      // ヒトの感染
      EACH( it_human, humans ) {                 // 各ヒトに対して
        (*it_human)->infection();                // 感染させる
      }
    }
#endif
    //----------------------------------------------------------------------
    //  ファイル出力
    //----------------------------------------------------------------------
    int infcount = 0;
    EACH( it_human, humans) {
      if ((*it_human)->isSusceptible())
      {
      } else {
        infcount++;
      }
    }
    output_value_with_term("inf-human.txt", infcount );
    output_value_with_term("tcell-size.txt", humans[0]->getTcellList().size() );
    output_value_with_term("dense.txt", humans[0]->getCellLand().calcDensityOfInfectedVirus() );
    output_value_with_term("isInfection.txt", humans[0]->isSymptomaticPeriod() );
  }
  //----------------------------------------------------------------------
  //  計算終了
  //----------------------------------------------------------------------
  ECHO("計算終了");
  Benchmark::Instance().stopTimer();
  LOG( virus->getTagString() );
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
  //  T細胞の移動
  EACH( it_tc, tcell_list ) {                    // 各T細胞に対して
    (*it_tc)->move(cell_land);                   // 移動させる
  }
  //  細胞の接触
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    VECTOR(Cell *) neighbors = cell_land.getNeighborsAt( **it_cell ); // 近隣の細胞を取得し
    EACH( it_neighbor, neighbors ) {
      (*it_cell)->contact( **it_neighbor );      // 接触させる
    }
  }
  //  細胞の感染
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    (*it_cell)->infection();                     // 感染させる
  }
  //  T細胞の殺傷
  VECTOR(Tcell *) new_tcell;
  EACH( it_tc, tcell_list ) {                    // 各T細胞に対して
    int x = (*it_tc)->getX();                    // 座標を
    int y = (*it_tc)->getY();                    // 取得して
    Cell& cell = cell_land.getCellAt(x, y);      // その位置の細胞を取得して
    if( cell.isInfected() )
    {                                            // 細胞が感染していて
      EACH( it_v, cell.getInfectedVirusList() )
      {                                          // 各感染ウイルスのどれかに対して
        if( (*it_tc)->hasReceptorMatching( **it_v ) )
        {                                        // 受容体を所持していれば
          if( probability( cell.calcDensityOfVirusSize() ) ) { // 細胞内のウイルス密度に比例して
            cell.clearInfectedViruses();         // ウイルスを除去して
            new_tcell.push_back( &( (*it_tc)->clone() ) ); // T細胞を増やす
            break;
          }
        }
      }
    }
  }
  EACH( it_tcell, new_tcell ) {                  // 新しいT細胞を
    tcell_list.push_back( *it_tcell );           // 追加する
  }
  //  T細胞の寿命
  for(ITERATOR(Tcell *)it=tcell_list.begin(); it!=tcell_list.end(); ) {
    (*it)->aging();                              // 老化する
    if ((*it)->willDie( TCELL_LIFESPAN )) {      // 寿命を超えれば
      human.eraseTcell( it );                    // 削除される
    } else {
      it++;
    }
  }
  while( ! human.enoughNumberOfTcellToRemove( TCELL_MINIMUM_SIZE ) ) {
    Tcell *newt = new Tcell( 10 );
    newt->randomLocate( cell_land );
    tcell_list.push_back( newt );
  }
  // ウイルスの増殖
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    if( (*it_cell)->isInfected() ) {             // 感染細胞ならば
      Virus *virus = (*it_cell)->getInfectedVirusList()[0]; // 先頭のウイルスを
      (*it_cell)->pushNewVirusCloneToInfectedVirusList( *virus ); // １つクローンする
    }
  }
}
