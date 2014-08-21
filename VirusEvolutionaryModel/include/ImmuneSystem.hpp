#ifndef ___IMMUNE_SYSTEM_HPP
#define ___IMMUNE_SYSTEM_HPP

class Virus;
class CellLand;

class ImmuneSystem
{
  public:
    ImmuneSystem();
    bool infection( Virus& v );

    CellLand& getCellLand() { return *cell_land_; }
  private:
    CellLand *cell_land_;
};

#endif
