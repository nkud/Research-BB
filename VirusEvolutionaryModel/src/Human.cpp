#include "Human.hpp"
#include "Virus.hpp"
#include "ImmuneSystem.hpp"
#include "Cell.hpp"

Human :: Human() :
  x_( 0 ),
  y_( 0 )
{
  immune_system_ = new ImmuneSystem();
}

int Human :: getX() const
{
  return x_;
}
int Human :: getY() const
{
  return y_;
}
void Human :: setX( int x )
{
  x_ = x;
}
void Human :: setY( int y )
{
  y_ = y;
}

VECTOR(Human *)& HumanLand :: getHumanAt( Human& human )
{
  int x = human.getX();
  int y = human.getY();
  int n = getHeight()*y + x;
  return human_list_[ n ];
}

HumanLand :: HumanLand( int width, int height ) :
  width_( width ),
  height_( height )
{
  human_list_ = new VECTOR(Human *)[ height * width ];
}
HumanLand :: ~HumanLand()
{
  SAFE_DELETE_ARRAY( human_list_ );
}
int HumanLand :: getWidth() const
{
  return width_;
}
int HumanLand :: getHeight() const
{
  return height_;
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
