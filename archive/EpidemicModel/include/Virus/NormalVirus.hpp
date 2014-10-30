#ifndef ___NORMAL_VIRUS
#define ___NORMAL_VIRUS

#include "VirusInterface.hpp"

class Gene;
class Life;

/** 
 * 通常ウイルス
 */
class NormalVirus : public __VirusInterface
{
  public:
    NormalVirus( const char *tag ) : __VirusInterface(tag) {}

    double getRate() const;
    NormalVirus& clone() {
      NormalVirus *virus = new NormalVirus(*this);
      return *virus;
    }
   int getInfectiousPeriod() const;
   int getNonInfectiousPeriod() const;
   int getLethalPeriod() const;
   int getMutationRate() const;
  private:
};

/** 
 * 区分ウイルス
 */
//class SectionedVirus : public __VirusInterface {
// public:
//   double getRate() const { return 0; }                              /* 感染確率を返す */
//   int getInfectiousPeriod() const;
//   int getNonInfectiousPeriod() const;
//   int getLethalPeriod() const;
//   int getMutationRate() const;
// private:
//};
#endif
