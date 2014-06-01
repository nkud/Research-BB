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

class Time {
  public:
    bool incrementTermTo( int max ) { if( term_++ < max ) return true; else return false; }
    int getTerm() const { return term_; }

    static Time& Instance() {
      static Time singleton;
      return singleton;
    }
  private:
    Time() : term_( 0 ) { }
    int term_;
};

#endif
