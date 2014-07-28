#include "NormalVirus.hpp"
#include "Function.h"
#include "Config.h"

/**
 * 感染性期間を返す
 */
int NormalVirus :: getInfectiousPeriod() const {
  return V_INFECTIOUS_PERIOD;
}

/**
 * 非感染性期間を返す
 */
int NormalVirus :: getNonInfectiousPeriod() const {
  return V_NONINFECTIOUS_PERIOD;
}

/**
 * 致死期間を返す
 */
int NormalVirus :: getLethalPeriod() const {
  return getInfectiousPeriod() + getNonInfectiousPeriod();
}

/**
 * 突然変異率を返す
 */
int NormalVirus :: getMutationRate() const {
  //  return V_MUTATION_RATE;
  //  double rate = 100
  double rate = 100*1./(1+value()/9.);
  return rate;
}

/**
 * 感染率を返す
 */
double NormalVirus :: getRate() const { 
  // return rate_; 
  //double rate = 100*1./(1+value()/9.);
  double rate = INFECTION_RATE;
  // LOG(rate)
  // double rate = 50.*((108-value())/108.);
  // double rate = 30;
  return rate;
}
