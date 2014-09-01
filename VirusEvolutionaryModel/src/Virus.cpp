#include "Virus.hpp"

Virus *Virus :: clone()
{
  Virus *newv = new Virus( getCString() );
//  Virus.getGene()                              // XXX
  return newv;
}
