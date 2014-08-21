#include "Tcell.hpp"
#include "Function.hpp"
#include "Landscape.hpp"

Tcell :: Tcell() :
  __Mobile(0, 0)
{
}

void Tcell :: randomLocate( __Landscape& land )
{
  int w = land.getWidth();
  int h = land.getHeight();
  setX( uniform_double(0,w) );
  setY( uniform_double(0,h) );
}

void Tcell :: move( __Landscape& land )
{
  int x = getX();
  int y = getY();
  if( rand_bool() )
    x += rand_bool() ? 1 : -1;
  if( rand_bool() )
    y += rand_bool() ? 1 : -1;
  x += land.getWidth();
  y += land.getHeight();
  setX( x%land.getWidth() );
  setY( y%land.getHeight() );
}
