/*
 * =====================================================================================
 *
 *       Filename:  FileFactory.cpp
 *
 *    Description:  
 *
 *         Author: Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include <fstream>
#include <ios>
#include <string>
#include <cstring>
#include <sstream>

#include "FileFactory.h"
#include "Agent.h"
#include "AgentManager.h"
#include "AgentCounter.h"
#include "VirusInterface.hpp"
#include "VirusManager.h"
#include "VirusCounter.h"
#include "Config.h"
#include "Benchmark.h"
#include "Term.h"

/*-----------------------------------------------------------------------------
 *  マクロ
 *-----------------------------------------------------------------------------*/
#define OFSV(str)                         do { ofs << #str << "," << (str) << std::endl; }while(0);
#define OFSVP(str,val)                    do { ofs << #str << "," << (val) << std::endl; }while(0);
#define OFSVV(str1,str2)                  do { ofs << #str1 << "," << #str2 << std::endl; }while(0);

#define ENDL                            std::endl

/**
 * @brief インスタンスを返す
 */
FileFactory& FileFactory :: Instance() {
    static FileFactory coredata;
    return coredata;                                                 /* インスタンスを返す */
}

/**
 * @brief マネージャーを設定
 */
void FileFactory :: setManager( AgentManager &am, VirusManager &vm ) {
    am_ = &am;                                                 /* 管理者を登録 */
    vm_ = &vm;                                                 /* 管理者を登録 */
}

/**
 * @brief 期間と数値を出力
 *
 * @detail 出力間隔を指定可能。デフォルトは１。
 */
void FileFactory :: outputValueWithTerm( const char *fname, int value, int interval ) const {
  if( Term::Instance().doAtInterval(interval) ) { // 指定された間隔ごとに
    std::ofstream ofs(fname, std::ios_base::out | std::ios_base::app);
    ofs << Term::Instance().getTerm() << SEPARATOR; // 期間と
    ofs << value << ENDL;                           // 数値を出力
  }

}

/**
 * @brief 計算後の情報を追加出力
 */
void FileFactory :: outputFile_appendLastInfo( const char *fname ) const {
  std::ofstream ofs(fname, std::ios_base::out | std::ios_base::app); /* インスタンスは１つだけ */
  
  int t = Term::Instance().getTerm(); /* 計算後実行期間 */
  int last_term;
  if( t < MINI_SIZE_TERM ) last_term = MINI_SIZE_TERM;
  else last_term = t - 1;
  
  OFSVP( LAST_TERM, last_term ); /* 実行期間 */
  
  ofs << "LAST_TERM," << last_term << ",実行期間";
  ofs << ENDL;
}

/**
 * @brief ウイルスのデータベースを出力
 *
 * @param fname ファイル名
 * @param dirname ディレクトリ名
 * @param interval 出力間隔
 */
void FileFactory ::
outputFile_VirusDataBase( const char *fname, const char *dirname, int interval ) const {
  if( Term::Instance().doAtInterval(interval) ) { // 指定の間隔で
    std::stringstream fstr;
    fstr << dirname << "/" << Term::Instance().getTerm() << "_" << fname; // ファイル名を作成
    std::ofstream ofs(fstr.str().c_str());
    
    int i = 0;
    EACH( it_v, VirusCounter::Instance().getVirusDataBase() ) {
      FOR(j, (*it_v)->getLen()) {
        ofs<<(*it_v)->tagAt(j);                                  /* ウイルスのタグ */
      }
      ofs << SEPARATOR << VirusCounter::Instance().getNumVirus(i++);
      ofs<<ENDL;
    }
    ofs.close();
  }
}

/**
 * @brief エージェントのデータベースを出力
 */
void FileFactory ::
outputFile_AgentDataBase( const char *fname, const char *dirname, int interval ) const {  
  if( Term::Instance().doAtInterval(interval) ) { // 指定の間隔で
    std::stringstream fstr;
    fstr << dirname << "/" << Term::Instance().getTerm() << "_" << fname; // ファイル名を作成
    std::ofstream ofs(fstr.str().c_str());
    EACH( it_a, am_->getAgentList() )
      {
        FOR(j, (*it_a)->getLen()) {
          ofs<<(*it_a)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs << SEPARATOR << (*it_a)->numHoldingVirus();                        /* エージェントの保持ウイルス数 */
        ofs << ENDL;
      }
    ofs.close();
  }
}
