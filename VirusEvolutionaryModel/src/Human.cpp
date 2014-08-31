#include "Human.hpp"
#include "Virus.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"


Human :: Human( int len, CellLand *land ) :
  __Life( len ),
  __Mobile(0, 0)
{
  // 細胞土地を初期化
  cell_land_ = land;

  // T細胞を初期化
  FOR( i, 100 ) {
    Tcell *newt = new Tcell( 10 );
    newt->randomLocate( getCellLand() );
    tcell_list_.push_back( newt );
  }
}

void Human :: pushVirusToStandByVirusList( Virus &virus ) {
  stand_by_virus_list_.push_back( &virus );
}

VECTOR(Human *)& HumanLand :: getHumanListAt( int x, int y )
{
  int n = getHeight()*y + x;
  return human_list_[ n ];
}

HumanLand :: HumanLand( int width, int height ) :
  __Landscape( width, height )
{
  human_list_ = new VECTOR(Human *)[ height * width ];
}
HumanLand :: ~HumanLand()
{
  SAFE_DELETE_ARRAY( human_list_ );
}
VECTOR(Virus *)& Human :: getInfectedVirusList() {
    int w = getCellLand().getWidth();
    infected_virus_list_.clear();
    FOR( i, w ) {
        EACH( it_v, getCellLand().getCellAt(i,0).getInfectedVirusList() ) {
            infected_virus_list_.push_back(*it_v);
        }
    }
    return infected_virus_list_;
}
//XXX
bool Human :: infection()
{
//  return can_infect;
  if( true ) {
    EACH( it_v, getStandByVirusList() ) {
      getCellLand().getCellAt(0,0).pushNewVirusCloneToInfectedVirusList(**it_v);
    }
    return true;
  }
  return false;
}

bool Human :: isSusceptible()
{
  if( getCellLand().calcInfectedCellDensity() <= 0 )
    return true;
  else
    return false;
}

bool Human :: isIncubationPeriod()
{
  double threshold = 0.2; // XXX
  if( getCellLand().calcInfectedCellDensity() < threshold )
    return true;
  else
    return false;
}

bool Human :: isSymptomaticPeriod()
{
  if( isIncubationPeriod() )
    return false;
  else
    return true;

}

void Human :: contact( __Host & neighbor )
{
  EACH( it_virus, neighbor.getInfectedVirusList() ) { // 感染ウイルスを取得して
   pushVirusToStandByVirusList( **it_virus );
  }
}

void HumanLand :: clearMap()
{
  int n = getWidth()*getHeight();
  FOR( i, n )
  {
    human_list_[i].clear();
  }
}

VECTOR(Human *) HumanLand :: getNeighborsAt( Human& human )
{
  VECTOR(Human *) neighbors;
  int x = human.getX();                          // 座標を
  int y = human.getY();                          // 取得する
  REP( i, -1, 1 ) {                              // 近隣の
    REP( j, -1, 1 ) {                            // それぞれに対して
      if( isOnMap(x+j, y+i) ) {
        VECTOR(Human *)& humans = getHumanListAt(x+j,y+i); // その位置のヒトを取得し
        EACH( it_human, humans ) {                 // 各ヒトに対して
          if( *it_human != &human )                // 自分でなければ
            neighbors.push_back( *it_human );      // 近隣リストに追加する
        }
      }
    }
  }
  return neighbors;                              // 近隣リストを返す
}

ITERATOR(Tcell *) Human :: eraseTcell( ITERATOR(Tcell *)& it_tcell ) {
  SAFE_DELETE( *it_tcell );
  ITERATOR(Tcell *)& it_next = it_tcell;
  tcell_list_.erase( it_tcell );
  return it_next;
}
void HumanLand :: resistHuman( Human& human )
{
  int x = human.getX();
  int y = human.getY();
  int n = getHeight()*y + x;
  human_list_[ n ].push_back( &human );
}

bool Human :: enoughNumberOfTcellToRemove( int min_tcell )
{
  if( getTcellListSize() > min_tcell )
    return true;
  else
    return false;
}

