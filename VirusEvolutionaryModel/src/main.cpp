#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"
#include "Random.hpp"
#include "FileFactory.hpp"
#include "Benchmark.hpp"
#include "VirusCounter.hpp"

#include "Config.hpp"

#include <sstream>

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
      new CellLand(CELL_LAND_WIDTH, CELL_LAND_HEIGHT, "0000000000")
      ); // 新しくヒトを初期化
    h->randomLocate(*humanLand);              // ランダムに土地に配置して
    humans.push_back( h );                    // 配列に追加していく
  }

  Virus *virus = new Virus( V_TAG );             // 新しいウイルスを初期化
  LOG( virus->getCString() );
  humans[0]->getCellLand().getCellAt(0,0).pushNewVirusCloneToInfectedVirusList(*virus);
  //----------------------------------------------------------------------
  //  計算開始
  //----------------------------------------------------------------------
  Benchmark::Instance().startTimer();
  ECHO("計算開始");
  while( term.loop() )                           // 最大実行期間までループする
  {
    // カウンターをリセット
    VirusCounter::Instance().clearData();

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
        Human& human = **it_human;
        EACH( it_neighbor, neighbors ) {
          Human& neighbor = **it_neighbor;
          // (*it_human)->contact( **it_neighbor ); // 接触させる
          if( neighbor.isSymptomaticPeriod() ) {
            EACH( it_virus, neighbor.getInfectedVirusList() ) { // 感染ウイルスを取得して
              Virus& virus = **it_virus;
              human.pushVirusToStandByVirusList( virus );
            }
          }
        }
      }
      // ヒトの感染
      // 待機ウイルスからランダムに１つ選び、
      // 感染せる
      EACH( it_human, humans ) {                 // 各ヒトに対して
        // XXX: あってる？？？？？
        Human& human = **it_human;
        // (*it_human)->infection();                // 感染させる
        if( human.isSusceptible() ) {                        // 未感染なら
          EACH( it_v, human.getStandByVirusList() ) {        // 各待機ウイルスに対して
            Cell& zerocell = human.getCellLand().getCellAt(0,0);
            Virus& virus = **it_v;
            zerocell.pushNewVirusCloneToInfectedVirusList(virus); // 左上に感染させる
            // XXX: １つだけ！！
            break;
          }
        }
        human.clearStandByViruses();
      }
    }
#endif
    
    //----------------------------------------------------------------------
    //  ファイル出力
    //----------------------------------------------------------------------

    // 感染者マップ
    if( Term::Instance().isInterval( 100 ) ) {
      std::stringstream hmap_fname;

      hmap_fname << Term::Instance().getTerm();
      hmap_fname << "_hmap.txt";
      std::ofstream hmap_ofs(hmap_fname.str());

      std::stringstream vvalue_fname;
      vvalue_fname << Term::Instance().getTerm();
      vvalue_fname << "_vvaluemap.txt";
      std::ofstream vvalue_ofs( vvalue_fname.str() );
    //   FOR( i, humanLand->getWidth() )
    //   {
    //     FOR( j, humanLand->getHeight() )
    //     {
    //       VECTOR(Human *)& humans = humanLand->getHumanListAt( i, j );
    //       if( humans.size() > 0 )
    //       {
    //         EACH( it_human, humans )
          //   {
          //     Human& human = **it_human;
          //     hmap_ofs << human.getX() << SEPARATOR;
          //     hmap_ofs << human.getY() << SEPARATOR;
          //     hmap_ofs << human.getCellLand().calcDensityOfInfectedVirus() << SEPARATOR;
          //     hmap_ofs << ENDL;
          //   }
          // }
          // hmap_ofs << ENDL;
    //     }
    //   }
      EACH( key, VirusCounter::Instance().getVirusValueMap() )
      {
        vvalue_ofs << (*key).first << SEPARATOR;
        vvalue_ofs << (*key).second << SEPARATOR;
        vvalue_ofs << ENDL;
      }
    }
    

    int infcount = 0;
    EACH( it_human, humans) {
      Human& human = **it_human;
      if (human.isSusceptible())
      {
      } else {
        ASSERT( human.isSymptomaticPeriod() || human.isIncubationPeriod() );
        infcount++;
      }
    }

    output_value_with_term("inf-human.txt", infcount );
    output_value_with_term("tcell-size.txt", humans[0]->getTcellList().size() );
    output_value_with_term("dense.txt", humans[0]->getCellLand().calcDensityOfInfectedVirus() );
    output_value_with_term("v-dense.txt", humans[0]->getCellLand().getCellAt(0,0).calcDensityOfVirusSize() );
    output_value_with_term("v-dense2.txt", humans[0]->getCellLand().getCellAt(0,1).calcDensityOfVirusSize() );
    output_value_with_term("isInfection.txt", humans[0]->isSymptomaticPeriod() );
    output_value_with_term("virus-size.txt", humans[0]->sizeOfAllInfectedViruses() );
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
    EACH( it_neighbor, neighbors )
    {                                            // 各近隣に対して
      double density = 100 * (*it_neighbor)->calcDensityOfVirusSize();
      Cell& cell = **it_cell;
      Cell& neighbor = **it_neighbor;
      if( density > V_ONE_STEP_GROWTH_THRESHOLD ) // ウイルス密度が閾値を超えていれば
      {
        // (*it_cell)->contact( **it_neighbor );      // 接触させる
        
        int size = neighbor.getInfectedVirusListSize();  // 近隣の感染ウイルスの中から
        int pos = uniform_int( 0, size-1 );              // ランダムに１つ選び
        Virus& virus = *( neighbor.getInfectedVirusList().at( pos ) ); // そのウイルスを
        cell.pushVirusToStandByVirusList( virus );  // 自分の待機ウイルスに追加する
        
        // cell.pushVirusToStandByVirusList( neighbor.popInfectedVirus() );
        // EACH( it_v, neighbor.getInfectedVirusList() ) {
        //   cell.pushVirusToStandByVirusList( **it_v );
        // }
      }
    }
  }
  //  細胞の感染
  int count_new_virus = 0;  // 新しいウイルス数をカウント
  int sum_new_virus_value = 0;  // 新しいウイルスの評価値をカウント
  EACH( it_cell, cell_list ) {                   // 各細胞に対して
    // (*it_cell)->infection();                     // 感染させる
    Cell& cell = **it_cell;
    if( cell.canPushNewVirus() ) 
    {                      // ウイルスに感染できる状態なら
      int n = cell.getStandByVirusList().size();  // 待機ウイルス数を取得して
      if( n > 0 )
      {
        int pos = uniform_int( 0, n-1 );       // 配列の中からランダムに１つ選び
        Virus& virus = *(cell.getStandByVirusList().at( pos )); // その待機ウイルスを取得する
        if( probability( virus.getInfectionRateForCell( cell ) ) ) // そのウイルス固有の感染率で
        {
          cell.pushNewVirusCloneToInfectedVirusList( virus );  // 感染させる
          if( Term::Instance().isInterval(10) ) {
            count_new_virus++;  // 新しいウイルス数をカウント
            sum_new_virus_value += virus.value(); // 新しいウイルスの評価値をカウント
            VirusCounter::Instance().addNewVirusData( virus );
          }
        }
      }
    }
    cell.clearStandByViruses();                         // 待機ウイルスをクリア
  }
  if( Term::Instance().isInterval(10) ){  // 平均評価値を出力
    double ave = 0;
    if( count_new_virus > 0 ) {
      ave = (double)sum_new_virus_value / count_new_virus;
      output_value_with_term("ave-newvirus-value.txt", ave );
    }
  }

  //  T細胞の殺傷
  VECTOR(Tcell *) new_tcell;
  EACH( it_tcell, tcell_list ) {                    // 各T細胞に対して
  	Tcell& tcell = **it_tcell;
    int x = tcell.getX();                    // 座標を
    int y = tcell.getY();                    // 取得して
    Cell& cell = cell_land.getCellAt(x, y);      // その位置の細胞を取得して
    if( cell.isInfected() )
    {                                            // 細胞が感染していて
      EACH( it_v, cell.getInfectedVirusList() )
      {                                          // 各感染ウイルスのどれかに対して
        if( tcell.hasReceptorMatching( **it_v ) )
        {                                        // 受容体を所持していれば
          if( probability( 100 * cell.calcDensityOfVirusSize() ) )
          {                                      // 細胞内のウイルス密度に比例して
            cell.clearInfectedViruses();         // ウイルスを除去して
            FOR( i, TCELL_CLONE_SIZE ) {         // T細胞のクローン数だけ
              Tcell& newtcell = tcell.clone();     // クローンを作成し
              if( probability( TCELL_MEMORY_RATE ) ) {  // 記憶率の確率で
                newtcell.becomeMemoryTcell();           // そのクローンをメモリーT細胞にする
              }
              new_tcell.push_back( &newtcell ); // T細胞を増やす
            }
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
  int count_normal_tcell = 0;
  FOREACH( it_tcell, tcell_list )
  {  // 全T細胞に対して
  	Tcell& tcell = **it_tcell;
    tcell.aging();                              // 老化する
    if ( ! tcell.isMemoryTcell() ) {
      count_normal_tcell++;
    }
    if (tcell.willDie( TCELL_LIFESPAN )) {      // メモリーT細胞ではなく寿命を超えれば
      human.eraseTcell( it_tcell );             // 削除して
    } else {
      it_tcell++;
    }
  }
  // while( ! human.enoughNumberOfTcellToRemove( TCELL_MINIMUM_SIZE ) ) {
  // 普通のT細胞を補完
  FOR( i, std::max( 0, TCELL_MINIMUM_SIZE - count_normal_tcell ) ) {
    Tcell *newt = new Tcell( TCELL_LEN );
    newt->randomLocate( cell_land );
    tcell_list.push_back( newt );
  }
  // ウイルスの増殖
  EACH( it_cell, cell_list )
  {                                              // 各細胞に対して
    Cell& cell = **it_cell;
    if( probability( V_REPRODUCTIVE_RATE ) )
    {                                            // 感染細胞かつ余裕があれば
      if( cell.canPushNewVirus() and cell.isInfected() )
      {                                          // 増殖率で
        Virus *virus = cell.getInfectedVirusList()[0]; // 先頭のウイルスを
        cell.pushNewVirusCloneToInfectedVirusList( *virus ); // １つクローンする
      }
    }
  }
}
