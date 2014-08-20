#include "Cell.hpp"
#include "Virus.hpp"
#include "Function.hpp"

Cell :: Cell() :
  infected_virus_list_( 0 ),
  stand_by_virus_list_( 0 )
{

}

bool Cell :: isInfected()
{
  if( getInfectedVirusList().size() > 0 )
    return true;
  else
    return false;
}

bool Cell :: isNotInfected()
{
  if( getInfectedVirusList().size() > 0 )
    return true;
  else
    return false;
}

VECTOR(Virus *)& Cell :: getInfectedVirusList()
{
  return infected_virus_list_;
}

VECTOR(Virus *)& Cell :: getStandByVirusList()
{
  return stand_by_virus_list_;
}

Cell& CellLand :: getCellAt( int x, int y )
{
  int n = getHeight()*y + x;
  return *cell_list_[ n ];
}
int CellLand :: getCellListSize() const
{
  return (int)cell_list_.size();
}
int CellLand :: getHeight()
{
  return height_;
}

CellLand :: CellLand( int width, int height ) :
  width_( width ),
  height_( height )
{

}
