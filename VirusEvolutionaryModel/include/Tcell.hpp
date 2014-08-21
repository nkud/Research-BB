#ifndef ___TCELL_HPP
#define ___TCELL_HPP

#include "Gene.hpp"
#include "Mobile.hpp"

class Virus;
class __Landscape;

class Tcell : public Gene, public __Mobile
{
  public:
    Tcell();
    ~Tcell();

    void move( __Landscape& land );
    void randomLocate( __Landscape& land );

    Tcell& clone();

    bool hasReceptorMatching( Virus &v );

    void reborn();

  private:
};

#endif
