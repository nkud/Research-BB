#include "Cell.hpp"
#include "Virus.hpp"
#include "Function.hpp"

Cell :: Cell(int x, int y) :
  __Location(x,y),
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

CellLand :: CellLand( int width, int height ) :
  __Landscape( width, height )
{
  // 新しい細胞を追加
  FOR( i, height ) {
    FOR( j, width ) {
      Cell *newc = new Cell(j, i);
      cell_list_.push_back( newc );
    }
  }
}

VECTOR(Cell *) CellLand :: getNeighborsAt( Cell& cell )
{
  VECTOR(Cell *) neighbors;
  int x = cell.getX();
  int y = cell.getY();
  REP( i, -1, 1 ) {
    REP( j, -1, 1 ) {
      Cell &cell = getCellAt(x+j,y+i);
      if( &cell == &cell ) continue;
      neighbors.push_back( &cell );
    }
  }
  return neighbors;
}

bool Cell :: canPushNewVirus()
{
  return true;
}

void Cell :: pushNewVirusCloneToInfectedVirusList( Virus& v )
{
  infected_virus_list_.push_back( new Virus() );
}

void Cell :: contact( VECTOR(Cell *)& neighbors )
{
  EACH( it_neighbor, neighbors )
  {
    EACH( it_v, (*it_neighbor)->getInfectedVirusList() )
    {
      if( canPushNewVirus() )
      {
        pushNewVirusCloneToInfectedVirusList( **it_v );
      }
    }
  }
}
