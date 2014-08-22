#include "Tcell.hpp"
#include "Function.hpp"
#include "Landscape.hpp"

Tcell :: Tcell() :
  __Mobile(0, 0)                                 // 座標(0, 0)で初期化
{
}

Tcell& Tcell :: clone()
{
  Tcell *newtcell = new Tcell();                 // 新しいT細胞を作成
  newtcell->setX(getX());                        // 座標を
  newtcell->setY(getY());                        // 同じ位置にして
  return *newtcell;                              // 返す
}
