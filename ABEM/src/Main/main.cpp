/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  説明を書く
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *   TODO:
 *      - new 系を Factory method で統一したい
 *      - readme
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
  VECTOR(Agent *) agent;                                             /* エージェントの配列 */
  VECTOR(Virus *) virus;                                             /* ウイルスの配列 */

  /* 管理者 */
  AgentManager aManager( agent );
  VirusManager vManager( virus );
  aManager.initAgent( 
      new RandomGaussWalk( A_MOVE_DISTANCE ),
      //    new RandomWalk( A_MOVE_DISTANCE ),
      new CoupleTag(), 
      // new Gene( A_DEFAULT_LEN ), 
      A_DEFAULT_LEN,
      A_INIT_NUM );
  vManager.initVirus();

  /* モニター・ファイル生成クラス */
  FileFactory &fFactory = FileFactory::Instance();                         /* 出力ファイルを管理 */
  AgentCounter::Instance().reset();
  VirusCounter::Instance().reset();
  fFactory.setManager( aManager, vManager );                                           /* 管理者を登録 */

  /*-----------------------------------------------------------------------------
   *  エージェントへの初期動作
   *-----------------------------------------------------------------------------*/
  /* エージェントへの初期感染 */
  FOR( i, V_NUM ) {
    virus[i]->getGene().printTag();
    aManager.initInfectAgentInRatio( *virus[i], A_INIT_INFECTED_RATE );    /* 初期感染させる */
  }

  int zero_count = 0;                                                /* 感染接触が起こらなかった数をカウント */
  /* 10回になると、計算を強制終了させる */

  /*-----------------------------------------------------------------------------
   *
   *  計算開始
   *
   *-----------------------------------------------------------------------------*/
  Term &term = Term::Instance();
  while( term.incrementTermTo(TERM) )                                /* 計算開始  */
  {
    /* カウンターのリセット */
    VirusCounter::Instance().reset();
    AgentCounter::Instance().reset();

    /* エージェント、ウイルス、土地の計算 */
#ifdef AGING_AGENT
    aManager.aging();                                              /* 老化する */
#endif
#ifdef MATING_AGENT
    aManager.mating();                                             /* 交配、出産する */
#endif
    // aManager.migrate();                                                    /* 移動する */
    /* MIGRATE */
    Landscape::Instance().clearAgentMap();
    EACH( it_a, agent ) {
      (*it_a)->move();
      Landscape::Instance().putAgentOnMap( **it_a );
      Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a );
    }
    /* CONTACT */
    EACH( it_a, agent ) {
      VECTOR(Agent *) neighbors = Landscape::Instance().getNeighbors( **it_a );
      if( neighbors.size() <= 0 ) continue;
      EACH( it_n, neighbors ) {
        assert( *it_a != *it_n );
        (**it_a).contact( **it_n );
      }
    }
    // aManager.contact();                                                    /* 近隣に接触する */
    /* INFECTION */
    ITERATOR(Virus *) itt;
    Virus *v;
    int n;
    int infection_count;                                               /* 同時感染数をカウント。最大値を越えないように */

    EACH( it_myself, agent )
    {
      if( (*it_myself)->getImmuneSystem()->hasNoStandByVirus() ) {     /* 待機ウイルスが無ければ */
        continue;                                                      /* スキップ */
      } else {                                                         /* あれば */
        infection_count = 0;

        while( ! (*it_myself)->getImmuneSystem()->hasNoStandByVirus() ) { /* 待機ウイルスがなくなるまで */
          if( infection_count >= A_MAX_V_INFECTED_ONE_TERM ) {         /* もし最大同時感染数を越えそうなら */
            break;                                                     /* 次のエージェントへ */
          }

          n = rand_array( (*it_myself)->getImmuneSystem()->getStandByVirusListSize() ); /* ランダムに一個の */
          v = (*it_myself)->getImmuneSystem()->getStandByVirusAt( n ); /* ウイルスを選んで */
          if( (*it_myself)->infection( *v ) ) {                        /* 感染させたら */
            infection_count++;                                         /* カウントを増やす */
          } else {
            itt = (*it_myself)->getImmuneSystem()->getStandByVirusListIteratorBegin();         /* もし感染しなければ */
            while(n-->0) { itt++; }                                    /* そのウイルスを */
            (*it_myself)->getImmuneSystem()->eraseStandByVirus( itt ); /* 待機ウイルスからはずして次のウイルス */
          }
        }
        (*it_myself)->getImmuneSystem()->clearStandByVirus();          /* 待機ウイルスをクリア */
      }
    }
    // aManager.infect();                                                     /* 待機ウイルスを感染させる */

    // aManager.response();                                                   /* 免疫応答（タグフリップ） */
    /* RESPONSE */
    EACH( it_a, agent )
    { 
      assert( (*it_a) != NULL );

      (*it_a)->response();                                             /* 免疫応答させる */

      if( (*it_a)->isLethal() ) {
        // it_a = deleteAgent( it_a );                                    /* 生存配列から削除される */
        (*it_a)->rebirth();
        AgentCounter::Instance().countUpRemoved();
      }
    }

    // XXX: data base
    FOR( j, (int)agent.size() ) {
      ITERATOR(Virus*) it_v=agent[j]->getImmuneSystem()->getVirusListIteratorBegin();
      while(it_v!=agent[j]->getImmuneSystem()->getVirusListIteratorEnd()) {
        VirusCounter::Instance().pushNewVirus(**it_v);
        it_v++;
      }
    }

    /*  途中経過出力 */
    fFactory.outputValueWithTerm( "A_population.txt", aManager.getAgentSize() );
    fFactory.outputValueWithTerm( "V_virusVariaty.txt", VirusCounter::Instance().getVirusVariaty() );
    fFactory.outputValueWithTerm( "A_isIncubation.txt", aManager.numIsIncubation() );
    fFactory.outputValueWithTerm( "A_isCrisis.txt", aManager.numIsCrisis() );
    fFactory.outputValueWithTerm( "A_hasViruses.txt", aManager.numHasVirus() );
    fFactory.outputValueWithTerm( "A_removed.txt", AgentCounter::Instance().getCountRemoved() );
    fFactory.outputValueWithTerm( "V_aveValue.txt", VirusCounter::Instance().calcAveValue() );

    if ( term.isInterval(500) )
    {
      char tfname[256], afname[256];
      sprintf(tfname, "%d_VirusDataBase.txt", term.getTerm() );
      sprintf(afname, "%d_AgentGeneDistribution.txt", term.getTerm() );
      fFactory.outputFile_LastVirusDataBase(tfname);
      /* Agent Gene Distribution */
      fFactory.outputFile_AgentGeneDistribution(afname);
    }

    /* 途中経過表示用ログ */
    cout << "===================================" << endl;
    // LOG( term.getTerm() << TERM );
    term.printTerm();
    Benchmark::Instance().printElapsedTime();
    LOG( agent.size() );
    LOG( agent[0]->getX() );
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
    if( (int)agent.size() == A_MAX_NUM ) break;
  } /* ============================================================== 計算終了 */

#ifdef BENCHMARK
  Benchmark::Instance().stopTimer();                                 /* ベンチマークの計測終了 */
  Benchmark::Instance().printTime();                                 /* 計測時間表示 */
#endif

  fFactory.outputFile_Info( "INFO.txt" );                                  /* プログラムの初期設定など出力 */
  fFactory.outputFile_LastLog( "Log.txt");
  fFactory.outputFile_LastVirusDataBase( "VirusDataBase.txt");
  aManager.printInitInfo();                                                /* 初期状態を表示 */
  vManager.printInitInfo();                                                /* 初期状態を表示 */

  // 確認用 -----------------------------------------------------------------
  LOG(sizeof(Agent));
  LOG(sizeof(Virus));
  LOG(sizeof(Relocate));
  LOG(sizeof(Term));

  return 0;
}
