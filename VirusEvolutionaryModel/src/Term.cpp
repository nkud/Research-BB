#include "Term.hpp"

#include <cassert>

Term :: Term() :
  term_( 0 ),
  max_term_( 0 ),
  human_interval_( 0 ),
  immune_interval_( 0 )
{

}

Term& Term :: Instance()
{
  static Term singleton;
  return singleton;
}

void Term :: setMaxTerm( int t )
{
  max_term_ = t;
}
int Term :: getMaxTerm()
{
  return max_term_;
}
int Term :: getTerm()
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

bool Term :: isHumanInterval() 
{
  if( getTerm()%human_interval_ == 0 )
    return true;
  else
    return false;
}
bool Term :: isImmuneInterval()
{
  if( getTerm()%immune_interval_ == 0 )
    return true;
  else
    return false;
}
void Term :: setHumanInterval( int t )
{
  human_interval_ = t;
}
void Term :: setImmuneInterval( int t )
{
  immune_interval_ = t;
}
