#ifndef ___CELL_HPP
#define ___CELL_HPP

#include "Function.hpp"
#include "Landscape.hpp"
#include "Mobile.hpp"

class Virus;

class Cell : public __Location
{
  public:
    Cell( int x, int y);
    bool isInfected();
    bool isNotInfected();

    void clearInfectedViruses();
    void clearStandByViruses();
    VECTOR(Virus *)& getInfectedVirusList();
    VECTOR(Virus *)& getStandByVirusList();

    void pushToStandByVirusList( Virus& v );
    void pushNewVirusCloneToInfectedVirusList( Virus& v );
    bool canPushNewVirus();

    void contact( VECTOR(Cell *)& neighbors );
    void infection();
  private:
    VECTOR(Virus *) infected_virus_list_;
    VECTOR(Virus *) stand_by_virus_list_;
};

class CellLand : public __Landscape
{
  public:
    CellLand( int width, int height );
    Cell& getCellAt( int x, int y );
    VECTOR(Cell *) getNeighborsAt( Cell& cell );
    VECTOR(Cell *)& getCellList(){ return cell_list_; }
    int getCellListSize() const;
  private:
    CellLand();
    VECTOR(Cell *) cell_list_;
};

#endif
