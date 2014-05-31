/*
 * =====================================================================================
 *
 *       Filename:  VirusManager.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "VirusManager.h"
#include "Virus.h"

/*-----------------------------------------------------------------------------
 *  VirusManager
 *-----------------------------------------------------------------------------*/
VirusManager :: VirusManager( VECTOR( Virus * ) &viruses ) :
  viruses_( viruses )
{
  LOG("init VirusManager");
}

void VirusManager :: initVirus() {
  LOG("init Viruses");
  /*-----------------------------------------------------------------------------
   *  ウイルスを初期化する
   *-----------------------------------------------------------------------------*/
  //                                   1234567890123456789
  viruses_.push_back( new Virus( V_TAG_0, new Normal ) );       /* 通常ウイルスを追加 */
  viruses_.push_back( new Virus( V_TAG_1, new Normal ) );       /* 通常ウイルスを追加 */
  //  viruses_->push_back( new Virus( 15, new Normal ) );          /* 通常ウイルスを追加 */
  //  viruses_->push_back( new Virus( 15, new Normal ) );          /* 通常ウイルスを追加 */
  //  virus.push_back( new Virus( 20, new Fixed(0) ) );                /* 固定ウイルスを追加 */
  //  virus.push_back( new Virus( 10, new Fixed(20) ) );               /* 固定ウイルスを追加 */
}
void VirusManager :: printInitInfo() {
  std::cout << "\nNUM_V:\t\t" << getVirusSize() << std::endl;

  std::cout << "VIRUS:" << std::endl;                                /* ウイルス情報 */
  FOR(i, getVirusSize()) {
    std::cout<<"\trate_"<<i<<":\t"<<viruses_[i]->getRate();
    std::cout<<"\tlen_"<<i<<":\t"<<viruses_[i]->getGene()->getLen()<<std::endl;
  }
  FOR( i, getVirusSize() ) {
    viruses_[i]->getGene()->printTag();       /* 全ウイルスのタグを表示 */
  }
}
