#include "Term.hpp"

#include <cassert>

Term& Term :: Instance()
{
  static Term singleton;
  return singleton;
}

int Term :: getRemainingTerm() const {
  return getMaxTerm() - getTerm();
}

double Term :: calcEstimatedRemainingTime()
{
  double now_time = Benchmark::Instance().getElapsedTime();
  int interval = getTerm() - prev_term_;
  double estimated_time = (now_time - prev_time_) / interval * getRemainingTerm();
  prev_time_ = now_time; 
  prev_term_ = getTerm();
  return estimated_time;
}

void Term :: setMaxTerm( int t )
{
  max_term_ = t;
}
int Term :: getMaxTerm() const
{
  return max_term_;
}
int Term :: getTerm() const
{
  return term_;
}

int Term :: incrementTerm()
{
  term_++;
  return term_;
}

bool Term :: loop() {
  incrementTerm();
  if( getTerm() <= getMaxTerm() )
    return true;
  else
    return false;
}

bool Term :: isInterval( int t ) const 
{
  if( getTerm()%t == 0 )
    return true;
  else
    return false;
}
