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
    bool isInfected();                     ///< 感染の真偽
    bool isNotInfected();                  ///< 未感染の真偽

    int getInfectedVirusListSize() { return infected_virus_list_.size(); }

    void clearInfectedViruses();
    void clearStandByViruses();
    VECTOR(Virus *)& getInfectedVirusList();
    VECTOR(Virus *)& getStandByVirusList();

    void pushToStandByVirusList( Virus& v );
    void pushNewVirusCloneToInfectedVirusList( Virus& v );
    bool canPushNewVirus();                      ///< 新しいウイルスを追加できるかの真偽

    void contact( VECTOR(Cell *)& neighbors );   ///< 接触する 
    bool infection();
  private:
    VECTOR(Virus *) infected_virus_list_;
    VECTOR(Virus *) stand_by_virus_list_;
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
    const VECTOR(Cell *)& getCellList() const { return cell_list_; }
    int getCellListSize() const;                 ///< 細胞数を取得する

    double calcInfectedCellDensity() const;      ///< 感染細胞の密度を計算する
    int countInfectedCell() const;               ///< 感染細胞の数を数える
  private:
    CellLand();
    VECTOR(Cell *) cell_list_;
};

#endif
