#ifndef ___TCELL_HPP
#define ___TCELL_HPP

#include "Gene.hpp"

class Tcell : public Gene
{
  public:
    int getX();
    int getY();
    void setX();
    void setY();
    void move();

    Tcell& clone();

    bool hasReceptorMatching( Virus &v );

    void reborn();

  private:
    int x_, y_;
}

#endif
