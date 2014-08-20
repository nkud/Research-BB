#include "Human.hpp"
#include "Virus.hpp"
#include "ImmuneSystem.hpp"

Human :: Human() :
  x_( 0 ),
  y_( 0 )
{

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

Human& HumanLand :: getHumanAt( int x, int y )
{
  int n = getHeight()*y + x;
  return *human_list_[ n ];
}

HumanLand :: HumanLand( int width, int height ) :
  width_( width ),
  height_( height )
{
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
