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

 #include <iostream>
 #include "Function.h"

class Term {
  public:
    bool incrementTermTo( int max ) { if( term_++ < max ) return true; else return false; }
    bool incrementTerm() { return incrementTermTo(getMaxTerm()); }
    int getTerm() const { return term_; }
    const int getMaxTerm() const { return max_term_; }

    static Term& Instance() {
      static Term singleton;
      return singleton;
    }
    void printTerm() const {
      std::cout << ">>> Term: " << getTerm() << " -> " << getMaxTerm() << std::endl;
    }

    void setMaxTerm( int max_term ) { max_term_ = max_term; }

    bool isInterval( int interval ) {
      if( getTerm() % interval == 0 ) return true; else return false;
    }

    void printStatusBar() {
      int n = 100 * (double)getTerm() / getMaxTerm();
      std::cout << "\n( " << n << " % )\n";
      std::cout << "[";
      FOR( i, n-1 ) {
        std::cout << RED << "=";
      }
      if( n > 0 ) std::cout << ">" << CLR_ST;
      FOR( i, 100-n ) {
        std::cout << " ";
      }
      std::cout << "]\n\n";
    }
  private:
    Term() : term_(0), max_term_(0) { }
    int term_;
    int max_term_;
};

#endif
