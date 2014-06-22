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
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

#include "Config.h"
#include "Function.h"
#include "Agent.h"
#include "AgentManager.h"
#include "Virus.h"
#include "VirusManager.h"
#include "Landscape.h"
#include "FileFactory.h"
#include "Term.h"

#include "VirusCounter.h"
#include "AgentCounter.h"

#ifdef BENCHMARK
#include "Benchmark.h"                                               
#endif

/*-----------------------------------------------------------------------------
 *
 *  メインルーチン
 *
 *-----------------------------------------------------------------------------*/
int main()
{
#ifdef BENCHMARK
  Benchmark::Instance().startTimer();                                /* ベンチマーク計測開始 */
#endif
  srand( (unsigned int)time(NULL)*time(NULL) );                      /* 乱数初期化 */

  /*-----------------------------------------------------------------------------
   *  初期化
   *-----------------------------------------------------------------------------*/
  VECTOR(Agent *) agents;                                            /* エージェントの配列 */
  VECTOR(Virus *) viruses;                                           /* ウイルスの配列 */
  Landscape &landscape = Landscape::Instance();

  /* 管理者 */
  AgentManager aManager( agents );                                   /* エージェントの配列を登録 */
  VirusManager vManager( viruses );                                  /* ウイルスの配列を登録 */

  /// プロトタイプを使う XXX
  aManager.initAgent( 
      new RandomGaussWalk( A_MOVE_DISTANCE ),
      //    new RandomWalk( A_MOVE_DISTANCE ),
      new CoupleTag(), 
      A_DEFAULT_LEN,
      A_INIT_NUM );
  vManager.initVirus();

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
  while( term.incrementTerm() )                                      /* 計算開始  */
  {
    /* カウンターのリセット */
    aCounter.reset();
    vCounter.reset();
    /* エージェント、ウイルス、土地の計算 */
#ifdef AGING_AGENT
    aManager.aging();                                                /* 老化する */
#endif
#ifdef MATING_AGENT
    aManager.mating();                                               /* 交配、出産する */
#endif
    /*-----------------------------------------------------------------------------
     *  移動
     *-----------------------------------------------------------------------------*/
    landscape.clearAgentMap();                                       /* エージェントの登録を初期化する */
    EACH( it_a, agents ) {                                           /* エージェントに対して */
      (*it_a)->move();                                               /* 移動させる */
      Landscape::Instance().putAgentOnMap( **it_a );                 /* 土地からはみ出してたら戻して */
      Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* 土地に登録する */
    }

    /*-----------------------------------------------------------------------------
     *  接触
     *-----------------------------------------------------------------------------*/
    EACH( it_a, agents ) {                                           /* エージェントに対して */
      VECTOR(Agent *) neighbors = landscape.getNeighbors( **it_a );  /* 近隣を取得する */
      if( neighbors.size() <= 0 ) continue;                          /* 近隣がいなければ次のエージェントへ */
      EACH( it_n, neighbors ) {                                      /* いればすべての近隣に対して */
        assert( *it_a != *it_n );
        (**it_a).contact( **it_n );                                  /* 接触する */
      }
    }
    /*-----------------------------------------------------------------------------
     *  感染
     *-----------------------------------------------------------------------------*/
    ITERATOR(Virus *) itt;
    Virus *v;
    int n;
    int infection_count;                                             /* 同時感染数をカウント。最大値を越えないように */

    EACH( it_myself, agents )
    {
      if( (*it_myself)->getImmuneSystem().hasNoStandByVirus() ) {   /* 待機ウイルスが無ければ */
        continue;                                                    /* スキップ */
      } else {                                                       /* あれば */
        infection_count = 0;

        while( ! (*it_myself)->getImmuneSystem().hasNoStandByVirus() ) { /* 待機ウイルスがなくなるまで */
          if( infection_count >= A_MAX_V_INFECTED_ONE_TERM ) {       /* もし最大同時感染数を越えそうなら */
            break;                                                   /* 次のエージェントへ */
          }

          n = rand_array( (*it_myself)->getImmuneSystem().getStandByVirusListSize() ); /* ランダムに一個の */
          v = (*it_myself)->getImmuneSystem().getStandByVirusAt( n ); /* ウイルスを選んで */
          if( (*it_myself)->infection( *v ) ) {                      /* 感染させたら */
            infection_count++;                                       /* カウントを増やす */
          } else {
            itt = (*it_myself)->getImmuneSystem().getStandByVirusListIteratorBegin();         /* もし感染しなければ */
            while(n-->0) { itt++; }                                  /* そのウイルスを */
            (*it_myself)->getImmuneSystem().eraseStandByVirus( itt ); /* 待機ウイルスからはずして次のウイルス */
          }
        }
        (*it_myself)->getImmuneSystem().clearStandByVirus();        /* 待機ウイルスをクリア */
      }
    }
    /*-----------------------------------------------------------------------------
     *  免疫応答
     *-----------------------------------------------------------------------------*/
    EACH( it_a, agents )
    { 
      assert( (*it_a) != NULL );

      (*it_a)->response();                                           /* 免疫応答させる */

      if( (*it_a)->isLethal() ) {
        // it_a = deleteAgent( it_a );                                    /* 生存配列から削除される */
        (*it_a)->rebirth();                                          // 初期化再生
        AgentCounter::Instance().countUpRemoved();
      }
    }
    /*-----------------------------------------------------------------------------
     *  症状進行 XXX name
     *-----------------------------------------------------------------------------*/
    EACH( it_a, agents )
    {
      EACH( it_v, (**it_a).getImmuneSystem().getVirusList() ) {      /* エージェントの保持ウイルス全てに対して */
        (*it_v)->incrementInfectionTime();                           /* ウイルス固有の感染期間を増やす */
        if( (*it_v)->isInfectiousPeriod() ) {                        /* ウイルスが感染性期間なら */
          (*it_v)->mutation( (*it_v)->getMutationRate() );           /* 突然変異を確率で起こす */
        }
      }
    }


    /*-----------------------------------------------------------------------------
     *  Virus データベース処理
     *-----------------------------------------------------------------------------*/
    EACH( it_a, agents ) {                                           /* 全エージェントの */
      EACH( it_v, (**it_a).getImmuneSystem().getVirusList() ) {      /* 全保持ウイルスに対して */
        VirusCounter::Instance().pushNewVirus(**it_v);               /* 新しいウイルスをデータベースに保存 */
      }
    }

    /*  途中経過出力 */
    fFactory.outputValueWithTerm( "A_population.txt", aManager.getAgentSize() );
    fFactory.outputValueWithTerm( "V_virusVariaty.txt", vCounter.getVirusVariaty() );
    fFactory.outputValueWithTerm( "A_isIncubation.txt", aManager.numIsIncubation() );
    fFactory.outputValueWithTerm( "A_isCrisis.txt", aManager.numIsCrisis() );
    fFactory.outputValueWithTerm( "A_hasViruses.txt", aManager.numHasVirus() );
    fFactory.outputValueWithTerm( "A_removed.txt", aCounter.getCountRemoved() );
    fFactory.outputValueWithTerm( "V_aveValue.txt", vCounter.calcAveValue() );
    fFactory.outputValueWithTerm( "A_aveValue.txt", aCounter.calcAveValue(agents) );

    if ( term.isInterval(DATABASE_INTERVAL) )
    {
      char tfname[256], afname[256];
      sprintf(tfname, "VirusDataBase/%d_VirusGeneDistribution.txt", term.getTerm() );
      sprintf(afname, "AgentDataBase/%d_AgentGeneDistribution.txt", term.getTerm() );
      fFactory.outputFile_LastVirusDataBase(tfname);
      fFactory.outputFile_AgentDataBase(afname);
    }

    /* 途中経過表示用ログ */
    cout << "===================================" << endl;
    // LOG( term.getTerm() << TERM );
    term.printTerm();
    Benchmark::Instance().printElapsedTime();
    LOG( agents.size() );
    LOG( agents[0]->getX() );
    LOG( AgentCounter::Instance().getCountRemoved() );
    LOG( aManager.getAgentSize() );
    LOG( AgentCounter::Instance().getCountContact() );
    LOG( AgentCounter::Instance().getCountInfectionContact() );
    LOG( aManager.numHasVirus() );
    LOG( VirusCounter::Instance().getCountMutation() );
    LOG( VirusCounter::Instance().getVirusVariaty() );

    /* 強制終了 */
    if( AgentCounter::Instance().getCountContact()==0 ) zero_count++;                   /* １０回以上接触感染がなければ */
    if( zero_count >= 20 ) break;                                    /* 強制的に終了する */
    if( (int)agents.size() == A_MAX_NUM ) break;
  }                                                                  /* ============================================================== 計算終了 */

#ifdef BENCHMARK
  Benchmark::Instance().stopTimer();                                 /* ベンチマークの計測終了 */
  Benchmark::Instance().printTime();                                 /* 計測時間表示 */
#endif

  fFactory.outputFile_Info( "info.txt" );                            /* プログラムの初期設定など出力 */
  fFactory.outputFile_LastLog( "last_log.txt");
  fFactory.outputFile_LastVirusDataBase( "LastVirusDataBase.txt");
  aManager.printInitInfo();                                          /* 初期状態を表示 */
  vManager.printInitInfo();                                          /* 初期状態を表示 */

  // 確認用 -----------------------------------------------------------------
  LOG(sizeof(Agent));
  LOG(sizeof(Virus));
  LOG(sizeof(Relocate));
  LOG(sizeof(Term));

  return 0;
}
