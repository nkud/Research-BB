/*
 * =====================================================================================
 *
 *       Filename:  VirusManager.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___VIRUS_MANAGER
#define ___VIRUS_MANAGER

#include "Global.h"

class Virus;

class VirusManager {
  public:
    VirusManager( VECTOR(Virus *) &viruses );
    void initVirus();

    ITERATOR(Virus *) getVirusIteratorBegin() { return viruses_.begin(); }
    ITERATOR(Virus *) getVirusIteratorEnd() { return viruses_.end(); }
    int getVirusSize() { return viruses_.size(); }

    void printInitInfo();                                      /* 初期状態の情報を端末に出力 */
  private:
    VECTOR(Virus *) &viruses_;
};

#endif
