/*
 * =====================================================================================
 *
 *       Filename:  Term.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___TERM
#define ___TERM

#include "Global.h"

class Term {
  public:
    bool incrementTermTo( int max ) { if( term_++ < max ) return true; else return false; }
    int getTerm() const { return term_; }

    static Term& Instance() {
      static Term singleton;
      return singleton;
    }
    void printTerm() const {
      std::cout << ">>> Term: " << getTerm() << " -> " << TERM << std::endl;
    }
  private:
    Term() : term_( 0 ) { }
    int term_;
};

#endif
