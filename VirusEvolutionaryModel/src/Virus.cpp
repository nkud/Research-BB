#include "Virus.hpp"

Virus *Virus :: clone()
{
  Virus *newv = new Virus();
//  Virus.getGene()                              // XXX
  return newv;
}
