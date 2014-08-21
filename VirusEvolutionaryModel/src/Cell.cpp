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
  // 保持ウイルスの最大値があれば、ここで処理
  int max_virus = 1;
  if( getInfectedVirusListSize() < max_virus )
    return true;
  else
    return false;
}

void Cell :: pushNewVirusToInfectedVirusList( Virus& v )
{
  infected_virus_list_.push_back( new Virus() );
}

void Cell :: contact( VECTOR(Cell *)& neighbors )
{
  // 接触する
  EACH( it_neighbor, neighbors )
  {
    EACH( it_v, (*it_neighbor)->getInfectedVirusList() )
    {
      pushCloneToStandByVirusList( **it_v );
    }
  }
}

void Cell :: pushCloneToStandByVirusList( Virus& v )
{
  stand_by_virus_list_.push_back( new Virus() );
}

bool Cell :: infection()
{
  // 待機ウイルスからランダムに選び、感染させる
  /// @todo 要変更
  if( canPushNewVirus() ) {
    EACH( it_v, getStandByVirusList() )
    {
      pushNewVirusToInfectedVirusList( **it_v );
    }
  }
  return false;
}

void Cell :: clearInfectedViruses()
{

}
void Cell :: clearStandByViruses()
{
  EACH( it_v, getStandByVirusList() ) {
    SAFE_DELETE( *it_v );
  }
  stand_by_virus_list_.clear();
}
