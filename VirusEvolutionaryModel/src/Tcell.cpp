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
  setX( uniform_int(0,1) );
  setY( uniform_int(0,h-1) );
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
