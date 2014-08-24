#ifndef ___CELL_HPP
#define ___CELL_HPP

#include "Function.hpp"
#include "Landscape.hpp"
#include "Mobile.hpp"
#include "Host.hpp"

class Virus;

class Cell : public __Location, public __Host
{
  public:
    Cell( int x, int y);
    bool isInfected();                           ///< 感染の真偽
    bool isNotInfected();                        ///< 未感染の真偽

    void contact( __Host& neighbor );            ///< 接触する 
    bool infection();
  private:
};

/**
 * @brief 細胞土地
 */
class CellLand : public __Landscape
{
  public:
    CellLand( int width, int height );
    Cell& getCellAt( int x, int y );
    VECTOR(Cell *) getNeighborsAt( Cell& cell ); ///< 近隣を取得する
    VECTOR(Cell *)& getCellList() { return cell_list_; }
    int getCellListSize() const;                 ///< 細胞数を取得する

    double calcInfectedCellDensity();            ///< 感染細胞の密度を計算する
    int countInfectedCell();                     ///< 感染細胞の数を数える
  private:
    CellLand();
    VECTOR(Cell *) cell_list_;
};

#endif
