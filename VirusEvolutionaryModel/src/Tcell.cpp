#include "Tcell.hpp"
#include "Function.hpp"
#include "Landscape.hpp"

Tcell :: Tcell( const char *tag ) :
  __Life( tag ),
  __Mobile( 0, 0 ),                               // 座標(0, 0)で初期化
  age_( 0 )
{
}
Tcell :: Tcell( int len ) :
  __Life( len ),
  __Mobile( 0, 0 ),                                 // 座標(0, 0)で初期化
  age_( 0 )
{
}

Tcell& Tcell :: clone()
{
  Tcell *newtcell = new Tcell( getGene().getCString() ); // 新しいT細胞を作成
  newtcell->setX(getX());                        // 座標を
  newtcell->setY(getY());                        // 同じ位置にして
  return *newtcell;                              // 返す
}

void Tcell :: aging()
{
  age_++;
}

bool Tcell :: willDie( int max_age ) const
{
  if( getAge() >= max_age )
    return true;
  else
    return false;
}
