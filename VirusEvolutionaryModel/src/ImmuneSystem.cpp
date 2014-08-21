#include "ImmuneSystem.hpp"
#include "Virus.hpp"
#include "Cell.hpp"

bool ImmuneSystem :: infection( Virus& v )
{
  return true;
}

ImmuneSystem :: ImmuneSystem()
{
  cell_land_ = new CellLand(10, 10);
}
