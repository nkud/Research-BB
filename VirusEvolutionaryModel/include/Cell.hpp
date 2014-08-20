#ifndef ___CELL_HPP
#define ___CELL_HPP

#include "Function.hpp"

class Virus;

class Cell
{
  public:
    Cell();
    bool isInfected();
    bool isNotInfected();

    void clearInfectedViruses();
    void clearStandByViruses();
    VECTOR(Virus *)& getInfectedVirusList();
    VECTOR(Virus *)& getStandByVirusList();

    void pushNewVirus( Virus *v );
    bool canPushNewVirus( Virus *v ) const;

    void contact( VECTOR(Cell *)& neighbors );
    void infection();
  private:
    VECTOR(Virus *) infected_virus_list_;
    VECTOR(Virus *) stand_by_virus_list_;
};


class CellLand
{
  public:
    CellLand( int width, int height );
    Cell& getCellAt( int x, int y );
    VECTOR(Cell *) getNeighborsAt( int x, int y ) const;
    VECTOR(Cell *) getCellList() const;
    int getCellListSize() const;

    int getWidth();
    int getHeight();
  private:
    CellLand();
    VECTOR(Cell *) cell_list_;
    int width_;
    int height_;
};

#endif
