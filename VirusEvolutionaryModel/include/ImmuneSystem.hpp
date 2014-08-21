#ifndef ___IMMUNE_SYSTEM_HPP
#define ___IMMUNE_SYSTEM_HPP

#include "Function.hpp"

class Virus;
class CellLand;
class Tcell;

class ImmuneSystem
{
  public:
    ImmuneSystem();
    bool infection( Virus& v );

    CellLand& getCellLand() { return *cell_land_; }
    VECTOR(Tcell *)& getTcellList() { return tcell_list; }

  private:
    CellLand *cell_land_;
    VECTOR(Tcell *) tcell_list;
};

#endif
