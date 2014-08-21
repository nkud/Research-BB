#include "Human.hpp"
#include "Virus.hpp"
#include "ImmuneSystem.hpp"
#include "Cell.hpp"
#include "Function.hpp"

Human :: Human() :
  __Mobile(0, 0)
{
  immune_system_ = new ImmuneSystem();
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

bool Human :: infection()
{
//  bool can_infect = immune_system_->infection( v );
//  return can_infect;
  return true;
}
void Human :: contact()
{

}

ImmuneSystem& Human :: getImmuneSystem()
{
  return *immune_system_;
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
