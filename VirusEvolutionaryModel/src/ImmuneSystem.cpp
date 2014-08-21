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
void ImmuneSystem :: pushCloneToStandByVirusList( Virus& virus )
{
  stand_by_virus_list_.push_back( new Virus() );
}

//XXX
VECTOR(Virus *) ImmuneSystem :: getInfectedVirusList()
{
  VECTOR(Virus *) virus_list;
  VECTOR(Virus *) infected = getCellLand().getCellAt(0,0).getInfectedVirusList();
  if( infected.size() > 0 ) {
    virus_list.push_back(infected[0]);
  }
  return virus_list;
}
