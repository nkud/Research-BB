#include "Cell.hpp"
#include "Virus.hpp"
#include "Function.hpp"
#include "Config.hpp"

Cell :: Cell(int x, int y, int clen) :
  __Location(x,y),
  __Life( clen ),
  max_virus_can_have_( CELL_MAX_VIRUS_CAN_HAVE )
{

}

bool Cell :: isInfected()
{
  if( getInfectedVirusListSize() > 0 )
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

double Cell :: calcDensityOfVirusSize() const
{
  double dense = 0;
  dense = (double)getInfectedVirusListSize() / getMaxSizeOfInfectedVirus();
  return dense;
}

void Cell :: contact( Cell& neighbor )
{
  EACH( it_v, neighbor.getInfectedVirusList() ) { // 感染ウイルスを取得し
    pushVirusToStandByVirusList( **it_v );       // 待機ウイルスに追加（クローンではない）
    // return;
  }
}

bool Cell :: infection()
{
  // 待機ウイルスからランダムに選び、感染させる
  /// @todo 要変更
  if( canPushNewVirus() ) 
  {                      // ウイルスに感染できる状態なら
    int n = getStandByVirusList().size();  // 待機ウイルス数を取得して
    if( n <= 0 ) return false;             // ０なら終了する
    int pos = uniform_int( 0, n-1 );       // 配列の中からランダムに１つ選び
    Virus& virus = *(getStandByVirusList().at( pos )); // そのウイルスを取得する
    if( probability( virus.getInfectionRate( *this ) ) ) // そのウイルス固有の感染率で
    {
      pushNewVirusCloneToInfectedVirusList( virus ); // 先頭だけ感染させる
      clearStandByViruses();  // 待機ウイルスをクリア
      return true;            // 終了
    }
    //EACH( it_v, getStandByVirusList() ) {        // 待機ウイルスの中から
      //Virus& virus = **it_v;
      //if( probability( virus.getInfectionRate() ) )
      //{
        //pushNewVirusCloneToInfectedVirusList( virus ); // 先頭だけ感染させる
        //clearStandByViruses();                     // 待機ウイルスをクリア
        //return true;                               // 終了
      //}
    //}
  }
  clearStandByViruses();                         // 待機ウイルスをクリア
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

void Cell :: clearInfectedViruses()
{
  EACH( it_v, getInfectedVirusList() ) {
    SAFE_DELETE( *it_v );
  }
  infected_virus_list_.clear();
}
void Cell :: clearStandByViruses()
{
  // EACH( it_v, getStandByVirusList() ) {
  //   SAFE_DELETE( *it_v );
  // }
  stand_by_virus_list_.clear();
}

void Cell :: pushNewVirusCloneToInfectedVirusList( Virus& v )
{
  infected_virus_list_.push_back( v.clone() ); // 同じウイルスを作成して追加
}
void Cell :: pushVirusToStandByVirusList( Virus& v )
{
  stand_by_virus_list_.push_back( &v ); // ウイルスへのポインタを追加
}

bool Cell :: canPushNewVirus()
{
  // 保持ウイルスの最大値があれば、ここで処理
  if( getInfectedVirusListSize() < getMaxSizeOfInfectedVirus() )
    return true;
  else
    return false;
}

//----------------------------------------------------------------------
//
//  CellLand
//
//----------------------------------------------------------------------
CellLand :: CellLand( int width, int height, int clen ) :
  __Landscape( width, height )                   // 土地を初期化
{
  // 新しい細胞を追加
  FOR( h, height ) {
    FOR( w, width ) {
      cell_list_.push_back( new Cell(w, h, clen) );
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

double CellLand :: calcDensityOfInfectedVirus()
{
  double dense = 0;
  dense = (double)countInfectedCell() / getCellListSize();
  return dense;
}
