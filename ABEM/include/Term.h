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
#include "Benchmark.h"

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
    int getRemainingTerm() { return getMaxTerm() - getTerm(); }

    double calcEstimatedRemainingTime() {
      static double prev_time = 0;
      static double estimated_time = -1;
      double now_time;
      int interval = 100;
      if( isInterval( interval ) ) {
        now_time = Benchmark::Instance().getElapsedTime();
        estimated_time = (now_time - prev_time) / interval * getRemainingTerm();
        prev_time = now_time; 
      }
      return estimated_time;
    }

    double progressRate() {
      double ret = 100 * (double)getTerm() / getMaxTerm();
      return ret;
    }

    void printStatusBar() {
      int n = (int)progressRate();
      std::cout << "\n";
      FOR( i, n ) {
        std::cout << GREEN_BG << " " << CLR_BG;
//        std::cout << GREEN << "|" << CLR_ST;
      }
//      if( n > 0 ) std::cout << ">" << CLR_ST;
      FOR( i, 100-n ) {
        std::cout << REVERSE << " " << STANDARD;
//        std::cout << RED << "|" << CLR_ST;
      }
      std::cout << " [ " << n << " % ] " << std::endl;
      double estimated_time = calcEstimatedRemainingTime();
      int estimated_min = estimated_time/60;
      int estimated_sec = estimated_time - estimated_min*60;
      std::cout << CLEAR_RIGHT << "\n>>> ESTIMATED REMAINING TIME: ";
      if ( estimated_time >= 0 ) {
        std::cout << CLEAR_RIGHT << UNDERLINE
         << estimated_min << " min " << estimated_sec << " sec"
         << STANDARD << std::endl;
      } else {
        std::cout << "calculating..." << std::endl;
      }
    }
  private:
    Term() : term_(0), max_term_(0) { }
    int term_;
    int max_term_;
};

#endif
