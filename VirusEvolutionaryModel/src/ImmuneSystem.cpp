#include "ImmuneSystem.hpp"
#include "Virus.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"

bool ImmuneSystem :: infection( Virus& v )
{
  return true;
}

ImmuneSystem :: ImmuneSystem()
{
  int w = 30;
  int h = 30;
  cell_land_ = new CellLand(w, h);
  FOR( i, 10 )
  {
    Tcell *newt = new Tcell();
    newt->randomLocate( getCellLand() );
    tcell_list.push_back( newt );
  }
}
