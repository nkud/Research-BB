#ifndef ___CELL_HPP
#define ___CELL_HPP

#include "Function.hpp"
#include "Virus.hpp"

class Cell
{
  public:
    bool isInfected();
    bool isNotInfected();

    void contact();
    void infection();
  private:
    VECTOR(Virus *) infected_virus_list_;
    VECTOR(Virus *) stand_by_virus_list_;;
};


class CellLand
{
  public:
    Cell& getHumanAt( int x, int y );
    VECTOR(Cell *) neighbors( int x, int y );
    VECTOR(Cell *) getCellList();
    int getCellListSize();

    int getWidth();
  private:
    VECTOR(Cell *) cell_list_;
    int width_;
};

#endif
