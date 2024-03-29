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

#include "Config.h"
#include "Function.h"

class __VirusInterface;

class VirusManager {
  public:
    VirusManager( VECTOR(__VirusInterface *) &viruses );

    ITERATOR(__VirusInterface *) getVirusIteratorBegin() { return viruses_.begin(); }
    ITERATOR(__VirusInterface *) getVirusIteratorEnd() { return viruses_.end(); }
    int getVirusSize() { return viruses_.size(); }

    void printInitInfo();                                      /* 初期状態の情報を端末に出力 */
  private:
    VECTOR(__VirusInterface *) &viruses_;
};

#endif
