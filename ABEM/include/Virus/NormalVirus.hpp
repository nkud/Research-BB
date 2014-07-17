#ifndef ___NORMAL_VIRUS
#define ___NORMAL_VIRUS

#include "Gene.h"
#include "VirusInterface.hpp"

class Gene;
class Life;

/** 
 * ウイルスのインターフェイス 
 */
class NormalVirus : public __VirusInterface
{
  public:
    NormalVirus( const char *tag ) : __VirusInterface(tag) {}

    /**
     * 感染率
     * @return
     */
    double getRate() const;
    /**
     * クローン
     * @return
     */
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
