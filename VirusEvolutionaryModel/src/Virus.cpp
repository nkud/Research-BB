#include "Virus.hpp"

Virus *Virus :: clone()
{
  Virus *newv = new Virus( getLen() );
//  Virus.getGene()                              // XXX
  return newv;
}
