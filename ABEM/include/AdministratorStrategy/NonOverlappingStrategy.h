/*
 * =====================================================================================
 *
 *       Filename:  NonOverlappingStrategy.h
 *
 *    Description:  
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___NONOVERLAPPING_STRATEGY
#define ___NONOVERLAPPING_STRATEGY

#include "AdministratorStrategy.h"

class __ModelStrategy;

/*-----------------------------------------------------------------------------
 *  NonOverlappingPopulation 戦略
 *-----------------------------------------------------------------------------*/
class NonOverlappingPopulation : public __ModelStrategy {
  public:
    virtual void aging();
    virtual void mating();
//    virtual void oneDay();
};

#endif
