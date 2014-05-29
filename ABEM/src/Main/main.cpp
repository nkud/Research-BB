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
#include "Landscape.h"
#include "Administrator.h"
#include "FileFactory.h"

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
//  Default *df = new Default;                                         /* モデル戦略 */
//  NonOverlappingPopulation *nlp = new NonOverlappingPopulation;      /* モデル戦略 */

  VECTOR(Agent *) agent;                                             /* エージェントの配列 */
  VECTOR(Virus *) virus;                                             /* ウイルスの配列 */
  Landscape &landscape = Landscape::Instance();

  /* 戦略 */
  Relocate *relocate = new Relocate;
  CoupleTag *couple_tag = new CoupleTag;

  /* 管理者 */
  Administrator admin( agent, virus, &landscape );                    /* 管理者に登録 */
  AgentManager am( agent );
  admin.initAgent( relocate, couple_tag, A_DEFAULT_LEN, A_INIT_NUM );            /* エージェント初期化 */
  am.initAgent( relocate, couple_tag, A_DEFAULT_LEN, A_INIT_NUM );
  admin.initVirus();                                                 /* ウイルス初期化 */

  /* モニター・ファイル生成クラス */
  FileFactory &ff = FileFactory::Instance();                         /* 出力ファイルを管理 */
  VirusCounter::Instance().reset();
  AgentCounter::Instance().reset();
  ff.setAdministrator( admin );                                      /* 管理者を登録 */

  /*-----------------------------------------------------------------------------
   *  エージェントへの初期動作
   *-----------------------------------------------------------------------------*/
  /* エージェントへの初期感染 */
  FOR( i, V_NUM ) {
    admin.initInfectAgentInRatio( *( new Virus( virus[i] ) ), A_INIT_INFECTED_RATE ); /* 初期感染させる */
  }
  /* 土地にランダムに配置 */
  admin.relocateAgent();                                             /* ランダムに配置 */

  int zero_count = 0;                                                /* 感染接触が起こらなかった数をカウント */
  /* 10回になると、計算を強制終了させる */

  /*-----------------------------------------------------------------------------
   *
   *  計算開始
   *
   *-----------------------------------------------------------------------------*/
  FOR( i, TERM )                                                     /* 計算開始  */
  {
    cout << "===================================" << endl;
    LOG( i );

    admin.incrementTerm();                                           /* 期間を進める */

    /* カウンターのリセット */
    VirusCounter::Instance().reset();
    AgentCounter::Instance().reset();


    /* エージェント、ウイルス、土地の計算 */
#ifdef AGING_AGENT
//    admin.agingAgent();                                              /* 老化する */
#endif
#ifdef MATING_AGENT
//    admin.matingAgant();                                             /* 交配、出産する */
#endif
    admin.moveAgent();                                               /* 移動する */
    admin.contactAgent();                                            /* 近隣に接触する */
    admin.infectAgent();                                             /* 待機ウイルスを感染させる */
    admin.responseAgent();                                           /* 免疫応答（タグフリップ） */

    // data base
    FOR( j, (int)agent.size() ) {
      ITERATOR(Virus*) it_v=agent[j]->getImmuneSystem()->getVirusListIteratorBegin();
      while(it_v!=agent[j]->getImmuneSystem()->getVirusListIteratorEnd()) {
        VirusCounter::Instance().pushNewVirus(**it_v);
        it_v++;
      }
    }

    /*  途中経過出力 */
    ff.outputFile_HasVirus              ( "A_hasVirus.txt"         ) ; /* 出力：感染者 */
    ff.outputFile_HasImmunity           ( "A_hasImmunity.txt"      ) ; /* 出力：免疫獲得者 */
    ff.outputFile_InfectionContactRatio ( "A_infectionContact.txt" ) ; /* 出力：接触回数 */
    ff.outputFile_Population            ( "A_population.txt"       ) ; /* 出力：人口 */
    ff.outputFile_VirusVariaty          ( "V_virusVariaty.txt"     ) ;

    if (i % 1000 == 0)
    {
      char tfname[256];
      sprintf(tfname, "%d_VirusDataBase.txt", i/10);
      ff.outputFile_LastVirusDataBase(tfname);
    }

    /* 途中経過表示用ログ */
    LOG( AgentCounter::Instance().getCountContact() );
    LOG( agent.size() );
    LOG( VirusCounter::Instance().getCountMutation() );
    LOG( VirusCounter::Instance().getVirusVariaty() );

    /* 強制終了 */
    if( AgentCounter::Instance().getCountContact()==0 ) zero_count++;                   /* １０回以上接触感染がなければ */
    if( zero_count >= 20 ) break;                                    /* 強制的に終了する */
    if( agent.size() == A_MAX_NUM ) break;
  } /* ============================================================== 計算終了 */

#ifdef ___BENCHMARK
  Benchmark::Instance().stopTimer();                                 /* ベンチマークの計測終了 */
  Benchmark::Instance().printTime();                                 /* 計測時間表示 */
#endif

  ff.outputFile_Info( "INFO.txt" );                                  /* プログラムの初期設定など出力 */
  ff.outputFile_LastLog( "Log.txt");
  ff.outputFile_LastVirusDataBase( "VirusDataBase.txt");
  admin.printInitInfo();                                             /* 初期状態を表示 */

  // 確認用 -----------------------------------------------------------------
  LOG(sizeof(Agent));
  LOG(sizeof(Virus));
  LOG(sizeof(admin));
  LOG(sizeof(Relocate));

  return 0;
}
