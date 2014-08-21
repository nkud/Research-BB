#include "Human.hpp"
#include "Virus.hpp"
#include "ImmuneSystem.hpp"
#include "Cell.hpp"

Human :: Human() :
  __Mobile(0, 0)
{
  immune_system_ = new ImmuneSystem();
}

VECTOR(Human *)& HumanLand :: getHumanAt( Human& human )
{
  int x = human.getX();
  int y = human.getY();
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

bool Human :: infection( Virus& v )
{
  bool can_infect = immune_system_->infection( v );
  return can_infect;
}

ImmuneSystem& Human :: getImmuneSystem()
{
  return *immune_system_;
}
