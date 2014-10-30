/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  ABEM program.
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *   TODO:
 *      - new 系を Factory method で統一したい
 *
 * =====================================================================================
 */

/**
 * @mainpage モデルの説明
 *
 * @section agent-infection 感染
 * 他者への感染は、ウイルスが感染性期間の時。現段階では症候性期間と同じ。
 *
 * @section virus-mutation 突然変異
 * ウイルスのみ、症候性期間の時に突然変異する。
 *
 * @todo コメントを整理する
 * @todo Configクラスを作成する
 */
/**
 * @file メイン関数 
 */

#include <sstream>

using namespace std;

#include "ABEMFramework.hpp"    // ABEMのフレームワーク

/**
 * @brief メインルーチン
 */
int main()
{
#ifdef BENCHMARK
  Benchmark::Instance().startTimer();                                /* ベンチマーク計測開始 */
#endif
  //-----------------------------------------------------------------------------
  //  初期化
  //-----------------------------------------------------------------------------
  VECTOR(Agent *) agents;                                            /* エージェントの配列 */
  VECTOR(__VirusInterface *) viruses;                                           /* ウイルスの配列 */
  Landscape &landscape = Landscape::Instance();

  /* 管理者 */
  AgentManager aManager( agents );                                   /* エージェントの配列を登録 */
  VirusManager vManager( viruses );                                  /* ウイルスの配列を登録 */

  /// エージェント初期化
  /// @note プロトタイプを用いた方がいいかも
  FOR( i, A_INIT_NUM ) {                                             /* num のだけ */
    agents.push_back( new Agent(
      new RandomGaussWalk( A_MOVE_DISTANCE ),
      A_DEFAULT_LEN )
    );                                                               /* 新しくエージェントを加える */
  }
  landscape.clearAgentMap();                                         /* エージェントの位置をリセット */
  int tx, ty;                                                        /* 移動させる場所 */
  EACH( it_a, agents ) {
    tx = rand_interval_int( 0, WIDTH-1 );                            /* ランダムに設定 */
    ty = rand_interval_int( 0, WIDTH-1 );
    (*it_a)->setX( tx );                                             /* 配置 */
    (*it_a)->setY( ty );
    landscape.registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* エージェントを登録 */
  }
  /// ウイルス初期化
  NormalVirus *virus = new NormalVirus( V_TAG_0 );
  viruses.push_back( virus );                                        /* 通常ウイルスを追加 */

  /* モニター・ファイル生成クラス */
  FileFactory& fFactory = FileFactory::Instance();                   /* 出力ファイルを管理 */
  AgentCounter& aCounter = AgentCounter::Instance();
  VirusCounter& vCounter = VirusCounter::Instance();
  aCounter.reset();
  vCounter.reset();
  fFactory.setManager( aManager, vManager );                         /* 管理者を登録 */

  /*-----------------------------------------------------------------------------
   *  エージェントへの初期動作
   *-----------------------------------------------------------------------------*/



  /* エージェントへの初期感染 */
  FOR( i, V_NUM ) {
    viruses[i]->getGene().printTag();
    aManager.initInfectAgentInRatio( *viruses[i], A_INIT_INFECTED_RATE );    /* 初期感染させる */
  }

  int zero_count = 0;                                                /* 感染接触が起こらなかった数をカウント */
  /* 10回になると、計算を強制終了させる */

  /*-----------------------------------------------------------------------------
   *
   *  計算開始
   *
   *-----------------------------------------------------------------------------*/
  Term &term = Term::Instance();
  term.setMaxTerm( TERM );
  TERMINAL_CLEAR;
  //  terminal_clear();
  while( term.incrementTerm() )                                      /* 計算開始  */
  {
    TERMINAL_LOCATION(0,0);
    CURSOR_CLEAR;
    //-----------------------------------------------------------------------------
    //  カウンターのリセット
    //
    aCounter.reset();
    vCounter.reset();

    //-----------------------------------------------------------------------------
    //  移動
    //
    landscape.clearAgentMap();                                       /* エージェントの登録を初期化する */
    EACH( it_a, agents ) {                                           /* エージェントに対して */
      (*it_a)->move();                                               /* 移動させる */
      Landscape::Instance().putAgentOnMap( **it_a );                 /* 土地からはみ出してたら戻して */
      Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* 土地に登録する */
    }

    //-----------------------------------------------------------------------------
    //  接触
    //
    EACH( it_a, agents ) {                                           /* エージェントに対して */
      VECTOR(Agent *) neighbors = landscape.getNeighbors( **it_a );  /* 近隣を取得する */
      if( neighbors.size() <= 0 ) continue;                          /* 近隣がいなければ次のエージェントへ */
      EACH( it_n, neighbors ) {                                      /* いればすべての近隣に対して */
        assert( *it_a != *it_n );
        (**it_a).contact( **it_n );                                  /* 接触する */
      }
    }
    //-----------------------------------------------------------------------------
    //  感染
    //
    ITERATOR(__VirusInterface *) itt;
    __VirusInterface *v;
    int n;
    int infection_count;                                             /* 同時感染数をカウント。最大値を越えないように */

    EACH( it_a, agents )
    {
      if( (*it_a)->getImmuneSystem().hasNoStandByVirus() )           /* 待機ウイルスが無ければ */
        continue;                                                    /* スキップ */

      infection_count = 0;
      while( ! (*it_a)->getImmuneSystem().hasNoStandByVirus() ) {    /* 待機ウイルスがなくなるまで */
        if( infection_count >= A_MAX_V_INFECTED_ONE_TERM ) {         /* もし最大同時感染数を越えそうなら */
          break;                                                     /* 次のエージェントへ */
        }

        // テンプレートを用いて、シャッフルの関数を定義できるかも
        // リストの数からランダムに一つ選び、それを返す関数
        n = rand_array( (*it_a)->getImmuneSystem().getStandByVirusListSize() ); /* ランダムに一個の */
        v = (*it_a)->getImmuneSystem().getStandByVirusAt( n );       /* ウイルスを選んで */
        if( (*it_a)->infection( *v ) ) {                             /* 感染させたら */
          infection_count++;                                         /* カウントを増やす */
        } else {
          itt = (*it_a)->getImmuneSystem().getStandByVirusListIteratorBegin();         /* もし感染しなければ */
          while(n-->0) { itt++; }                                    /* そのウイルスを */
          (*it_a)->getImmuneSystem().eraseStandByVirus( itt );       /* 待機ウイルスからはずして次のウイルス */
        }
      }
      (*it_a)->getImmuneSystem().clearStandByVirus();                /* 待機ウイルスをクリア */
    }
    //-----------------------------------------------------------------------------
    //  症状進行
    //
    EACH( it_a, agents )
    {
      EACH( it_v, (**it_a).getImmuneSystem().getVirusList() ) {      /* エージェントの保持ウイルス全てに対して */
        if( (*it_v)->isInfectiousPeriod() ) {                        /* ウイルスが感染性期間なら */
          assert( (**it_a).isSymptomaticPeriod() and "エージェントは症候性期間" );
          (*it_v)->mutation( (*it_v)->getMutationRate() );           /* 突然変異を確率で起こす */
        }
        (*it_v)->incrementInfectionTime();                           /* ウイルス固有の感染期間を増やす */
      }
    }
    //-----------------------------------------------------------------------------
    //  免疫応答
    //
    EACH( it_a, agents )
    { 
      (*it_a)->response();                                           /* 免疫応答させる */

      if( (*it_a)->isLethal() ) {
        // it_a = deleteAgent( it_a );                                    /* 生存配列から削除される */
        (*it_a)->rebirth();                                          // 初期化再生
        AgentCounter::Instance().countUpRemoved();
      }
    }


    //  ウイルスデータベース処理
    EACH( it_a, agents ) {                                           /* 全エージェントの */
      EACH( it_v, (**it_a).getImmuneSystem().getVirusList() ) {      /* 全保持ウイルスに対して */
        VirusCounter::Instance().pushNewVirus(**it_v);               /* 新しいウイルスをデータベースに保存 */
      }
    }

    //-----------------------------------------------------------------------------
    //  途中経過出力
    fFactory.outputValueWithTerm( "A_population.txt", aManager.getAgentSize() );
    fFactory.outputValueWithTerm( "V_virusVariaty.txt", vCounter.getVirusVariaty() );
    fFactory.outputValueWithTerm( "A_isIncubation.txt", aManager.numIsIncubation() );
    fFactory.outputValueWithTerm( "A_isCrisis.txt", aManager.numIsCrisis() );
    fFactory.outputValueWithTerm( "A_hasViruses.txt", aManager.numHasVirus() );
    fFactory.outputValueWithTerm( "A_removed.txt", aCounter.getCountRemoved() );
    fFactory.outputValueWithTerm( "V_aveValue.txt", vCounter.calcAveValue() );
    fFactory.outputValueWithTerm( "A_aveValue.txt", aCounter.calcAveValue(agents) );
    
    fFactory.outputFile_VirusDataBase("AgentGeneDistribution.txt", "AgentDataBase", DATABASE_INTERVAL);
    fFactory.outputFile_AgentDataBase("VirusGeneDistribution.txt", "VirusDataBase", DATABASE_INTERVAL);    
    
    //-----------------------------------------------------------------------------
    // 途中経過表示
    // LOG( term.getTerm() << TERM );
    term.printTerm();
    Benchmark::Instance().printElapsedTime();
    // LOG( agents.size() );
    // LOG( agents[0]->getX() );
    LOG( AgentCounter::Instance().getCountRemoved() );
    // LOG( aManager.getAgentSize() );
    LOG( AgentCounter::Instance().getCountContact() );
    LOG( AgentCounter::Instance().getCountInfectionContact() );
    // LOG( aManager.numHasVirus() );
    LOG( VirusCounter::Instance().getCountMutation() );
    LOG( VirusCounter::Instance().getVirusVariaty() );
    term.printProgressBar();
    

    /* 強制終了 */
    if( AgentCounter::Instance().getCountContact()==0 ) zero_count++; /* １０回以上接触感染がなければ */
    if( zero_count >= 20 ) break; /* 強制的に終了する */
    if( (int)agents.size() == A_MAX_NUM ) break;
    
  } /* ============================================================== 計算終了 */

#ifdef BENCHMARK
  Benchmark::Instance().stopTimer();                                 /* ベンチマークの計測終了 */
  Benchmark::Instance().printTime();                                 /* 計測時間表示 */
#endif

  fFactory.outputFile_appendLastInfo( "INFO.txt" ); /* 実行情報を追加出力 */
  
  aManager.printInitInfo();     /* 初期状態を表示 */
  vManager.printInitInfo();     /* 初期状態を表示 */

  // 確認用 ---------------------------------------------------------------------
  LOG(sizeof(Agent));
  LOG(sizeof(__VirusInterface));
  LOG(sizeof(Relocate));
  LOG(sizeof(Term));
  //-----------------------------------------------------------------------------

  return 0;
}
