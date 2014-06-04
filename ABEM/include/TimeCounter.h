/*
 * =====================================================================================
 *
 *       Filename:  Time.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___TIME
#define ___TIME

#include "Global.h"

class Time {
  public:
    bool incrementTermTo( int max ) { if( term_++ < max ) return true; else return false; }
    int getTerm() const { return term_; }

    static Time& Instance() {
      static Time singleton;
      return singleton;
    }
    void printTerm() const {
      std::cout << getTerm() << " -> " << TERM << std::endl;
    }
  private:
    Time() : term_( 0 ) { }
    int term_;
};

#endif
