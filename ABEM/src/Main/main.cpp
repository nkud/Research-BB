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

#include "Global.h"
#include "Function.h"
#include "Agent.h"
#include "AgentManager.h"
#include "Virus.h"
#include "VirusManager.h"
#include "Landscape.h"
#include "FileFactory.h"
#include "TimeCounter.h"

#include "VirusCounter.h"
#include "AgentCounter.h"

#ifdef ___BENCHMARK
#include "Benchmark.h"
#endif

/*-----------------------------------------------------------------------------
 *
 *  メインルーチン
 *
 *-----------------------------------------------------------------------------*/
int main()
{
#ifdef ___BENCHMARK
  Benchmark::Instance().startTimer();                                /* ベンチマーク計測開始 */
#endif
  srand( (unsigned int)time(NULL)*time(NULL) );                      /* 乱数初期化 */

  /*-----------------------------------------------------------------------------
   *  初期化
   *-----------------------------------------------------------------------------*/
  VECTOR(Agent *) agent;                                             /* エージェントの配列 */
  VECTOR(Virus *) virus;                                             /* ウイルスの配列 */

  /* 戦略 */
  Relocate *relocate = new Relocate;
  CoupleTag *couple_tag = new CoupleTag;

  /* 管理者 */
  AgentManager am( agent );
  VirusManager vm( virus );
  am.initAgent( relocate, couple_tag, A_DEFAULT_LEN, A_INIT_NUM );
  vm.initVirus();

  /* モニター・ファイル生成クラス */
  FileFactory &ff = FileFactory::Instance();                         /* 出力ファイルを管理 */
  AgentCounter::Instance().reset();
  VirusCounter::Instance().reset();
  ff.setManager( am, vm );                                           /* 管理者を登録 */

  /*-----------------------------------------------------------------------------
   *  エージェントへの初期動作
   *-----------------------------------------------------------------------------*/
  /* エージェントへの初期感染 */
  FOR( i, V_NUM ) {
    virus[i]->getGene()->printTag();
    am.initInfectAgentInRatio( *virus[i], A_INIT_INFECTED_RATE );    /* 初期感染させる */
  }

  int zero_count = 0;                                                /* 感染接触が起こらなかった数をカウント */
  /* 10回になると、計算を強制終了させる */

  /*-----------------------------------------------------------------------------
   *
   *  計算開始
   *
   *-----------------------------------------------------------------------------*/
  Time &time = Time::Instance();
  while( time.incrementTermTo(TERM) )                                /* 計算開始  */
  {
    /* カウンターのリセット */
    VirusCounter::Instance().reset();
    AgentCounter::Instance().reset();


    /* エージェント、ウイルス、土地の計算 */
#ifdef AGING_AGENT
    am.aging();                                              /* 老化する */
#endif
#ifdef MATING_AGENT
    am.mating();                                             /* 交配、出産する */
#endif
    am.migrate();                                                    /* 移動する */
    am.contact();                                                    /* 近隣に接触する */
    am.infect();                                                     /* 待機ウイルスを感染させる */
    am.response();                                                   /* 免疫応答（タグフリップ） */

    // data base
    FOR( j, (int)agent.size() ) {
      ITERATOR(Virus*) it_v=agent[j]->getImmuneSystem()->getVirusListIteratorBegin();
      while(it_v!=agent[j]->getImmuneSystem()->getVirusListIteratorEnd()) {
        VirusCounter::Instance().pushNewVirus(**it_v);
        it_v++;
      }
    }

    /*  途中経過出力 */
    ff.outputFile( "A_population.txt", am.getAgentSize() );
    ff.outputFile( "V_virusVariaty.txt", VirusCounter::Instance().getVirusVariaty() );
    ff.outputFile( "A_isIncubation.txt", am.numIsIncubation() );
    ff.outputFile( "A_isCrisis.txt", am.numIsCrisis() );
    ff.outputFile( "A_hasViruses.txt", am.numHasVirus() );

    if ( time.getTerm() % 1000 == 0)
    {
      char tfname[256];
      sprintf(tfname, "%d_VirusDataBase.txt", time.getTerm()/1000);
      ff.outputFile_LastVirusDataBase(tfname);
    }

    /* 途中経過表示用ログ */
    cout << "===================================" << endl;
    LOG( time.getTerm() );
    LOG( agent.size() );
    LOG( am.getAgentSize() );
    LOG( AgentCounter::Instance().getCountContact() );
    LOG( AgentCounter::Instance().getCountInfectionContact() );
    LOG( am.numHasVirus() );
    LOG( VirusCounter::Instance().getCountMutation() );
    LOG( VirusCounter::Instance().getVirusVariaty() );

    /* 強制終了 */
    if( AgentCounter::Instance().getCountContact()==0 ) zero_count++;                   /* １０回以上接触感染がなければ */
    if( zero_count >= 20 ) break;                                    /* 強制的に終了する */
    if( (int)agent.size() == A_MAX_NUM ) break;
  } /* ============================================================== 計算終了 */

#ifdef ___BENCHMARK
  Benchmark::Instance().stopTimer();                                 /* ベンチマークの計測終了 */
  Benchmark::Instance().printTime();                                 /* 計測時間表示 */
#endif

  ff.outputFile_Info( "INFO.txt" );                                  /* プログラムの初期設定など出力 */
  ff.outputFile_LastLog( "Log.txt");
  ff.outputFile_LastVirusDataBase( "VirusDataBase.txt");
  am.printInitInfo();                                                /* 初期状態を表示 */
  vm.printInitInfo();                                                /* 初期状態を表示 */

  // 確認用 -----------------------------------------------------------------
  LOG(sizeof(Agent));
  LOG(sizeof(Virus));
  LOG(sizeof(Relocate));

  return 0;
}
