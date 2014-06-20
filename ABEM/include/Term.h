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
  private:
    Term() : term_(0), max_term_(0) { }
    int term_;
    int max_term_;
};

#endif
