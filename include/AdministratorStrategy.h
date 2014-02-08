/* =====================================================================================
 *
 *       Filename:  AdministratorStrategy.h
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * ================================================================================== */

#ifndef ___ADMINISTRATOR_STRATEGY
#define ___ADMINISTRATOR_STRATEGY

class Administrator;

/* =====================================================================================
 *        Class:  __ModelStrategy
 *  Description:  数理モデルの戦略
 * ================================================================================== */
class __ModelStrategy {
  public:
    virtual void start(Administrator *ad) = 0;
};

#endif
