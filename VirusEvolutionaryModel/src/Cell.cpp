#include "Cell.hpp"
#include "Virus.hpp"
#include "Function.hpp"

Cell :: Cell(int x, int y) :
  __Location(x,y)
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
  if( isInfected() )
    return false;
  else
    return true;
}



void Cell :: contact( __Host& neighbor )
{
    EACH( it_v, neighbor.getInfectedVirusList() ) { // 感染ウイルスを取得し
      pushVirusToStandByVirusList( **it_v );     // 待機ウイルスに追加（クローンではない）
    }
}

bool Cell :: infection()
{
  // 待機ウイルスからランダムに選び、感染させる
  /// @todo 要変更
  if( canPushNewVirus() ) {                      // ウイルスに感染できる状態なら
    EACH( it_v, getStandByVirusList() ) {        // 待機ウイルスの中から
      pushNewVirusCloneToInfectedVirusList( *(*it_v)->clone() ); // 感染させる
      clearStandByViruses();                     // 待機ウイルスをクリア
      return true;                               // 終了
    }
  }
  clearStandByViruses();                         // 待機ウイルスをクリア
  return false;
}

//----------------------------------------------------------------------
//
//  CellLand
//
//----------------------------------------------------------------------
CellLand :: CellLand( int width, int height ) :
  __Landscape( width, height )                   // 土地を初期化
{
  // 新しい細胞を追加
  FOR( h, height ) {
    FOR( w, width ) {
      cell_list_.push_back( new Cell(w, h) );
    }
  }
}

int CellLand :: countInfectedCell()
{
  int num = 0;
  EACH( it_cell, getCellList() ) {               // 各細胞に対して
    if( (*it_cell)->isInfected() ) {             // 感染していれば
      num++;                                     // カウントする
    }
  }
  return num;
}

Cell& CellLand :: getCellAt( int x, int y )
{
  int n = getHeight()*y + x;
  return *cell_list_[ n ];
}
int CellLand :: getCellListSize() const
{
  return getWidth()*getHeight();
  //return (int)cell_list_.size();
}

VECTOR(Cell *) CellLand :: getNeighborsAt( Cell& cell )
{
  VECTOR(Cell *) neighbors;
  int x = cell.getX();
  int y = cell.getY();
  REP( i, -1, 1 ) {
    REP( j, -1, 1 ) {
      if( isOnMap(x+j, y+i) ) {                  // 土地の上なら
        Cell &neighbor = getCellAt(x+j,y+i);
        if( &neighbor == &cell ) continue;
        neighbors.push_back( &neighbor );
      }
    }
  }
  return neighbors;
}

double CellLand :: calcInfectedCellDensity()
{
  double dense = 0;
  dense = (double)countInfectedCell() / getCellListSize();
  return dense;
}