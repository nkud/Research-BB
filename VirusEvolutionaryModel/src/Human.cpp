#include "Human.hpp"
#include "Virus.hpp"
#include "Cell.hpp"
#include "Tcell.hpp"
#include "Function.hpp"
#include "Config.hpp"


Human :: Human( int tlen, int tsize, CellLand *land ) :
  __Mobile(0, 0)
{
  // 細胞土地を初期化
  cell_land_ = land;

  // T細胞を初期化
  FOR( i, tsize ) {
    Tcell *newt = new Tcell( tlen );
    newt->randomLocate( getCellLand() );
    tcell_list_.push_back( newt );
  }
}

void Human :: pushVirusToStandByVirusList( Virus &virus ) {
  stand_by_virus_list_.push_back( &virus );
}

int Human :: sizeOfAllInfectedViruses()
{
  int ret = 0;
  EACH( it_cell, getCellLand().getCellList() )
  {
    Cell& cell = **it_cell;
    ret += cell.getInfectedVirusListSize();
  }
  return ret;
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


//--------------------------------------------------------------------------------------
//       Class:  Human
//      Method:  getInfectedVirusList
// Description:  
//--------------------------------------------------------------------------------------
VECTOR(Virus *)& Human :: getInfectedVirusList() {
  int w = getCellLand().getWidth();
  infected_virus_list_.clear();
  FOR( i, w ) {
    EACH( it_v, getCellLand().getCellAt(i,0).getInfectedVirusList() ) {
      infected_virus_list_.push_back(*it_v);     // 感染ウイルスに加える
    }
  }
  return infected_virus_list_;
}

//--------------------------------------------------------------------------------------
//       Class:  Human
//      Method:  infection
// Description:  
//--------------------------------------------------------------------------------------
//XXX
bool Human :: infection()
{
//  return can_infect;
  if( isSusceptible() ) {                        // 未感染なら
    EACH( it_v, getStandByVirusList() ) {        // 各待機ウイルスに対して
      getCellLand().getCellAt(0,0).pushNewVirusCloneToInfectedVirusList(*((*it_v)->clone())); // 左上に感染させる
      // XXX: １つだけ！！
      clearStandByViruses();
      return true;
    }
    clearStandByViruses();
    return true;
  }
  clearStandByViruses();
  return false;
}

//--------------------------------------------------------------------------------------
//       Class:  Human
//      Method:  clearStandByViruses
// Description:  
//--------------------------------------------------------------------------------------
void Human :: clearStandByViruses()
{
  //EACH( it_v, getStandByVirusList() ) {
    //SAFE_DELETE( *it_v );
  //}
  stand_by_virus_list_.clear();
}

//--------------------------------------------------------------------------------------
//       Class:  Human
//      Method:  isSusceptible
// Description:  
//--------------------------------------------------------------------------------------
bool Human :: isSusceptible()
{
  if( getCellLand().calcDensityOfInfectedVirus() <= 0 )
    return true;
  else
    return false;
}

bool Human :: isIncubationPeriod()
{
  // double threshold = 0.6; // XXX
  int threshold = H_SYMPTOMATIC_THRESHOLD;
  if( getCellLand().calcDensityOfInfectedVirus() < ((double)threshold/100) )
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

void Human :: contact( Human & neighbor )
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

