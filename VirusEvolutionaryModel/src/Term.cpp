#include "Term.hpp"

#include <cassert>

Term :: Term() :
  term_( 0 ),
  max_term_( 0 )
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
