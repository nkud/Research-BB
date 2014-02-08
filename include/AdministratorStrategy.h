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
 *  TODO: why do i need have to set pure virtual??
 * ================================================================================== */
class __ModelStrategy {
  public:
    /*-----------------------------------------------------------------------------
     *  各フェイズ
     *-----------------------------------------------------------------------------*/
    virtual void aging(Administrator &ad) = 0;
    virtual void mating(Administrator &ad) = 0;
    virtual void migrate(Administrator &ad) = 0;
    virtual void contact(Administrator &ad) = 0;
    virtual void infect(Administrator &ad) = 0;
    virtual void response(Administrator &ad) = 0;
    /*-----------------------------------------------------------------------------
     *  すべてプロセスを実行
     *-----------------------------------------------------------------------------*/
    virtual void oneDay(Administrator &ad) = 0;
};

/*-----------------------------------------------------------------------------
 *  デフォルトの戦略
 *-----------------------------------------------------------------------------*/
class Default : public __ModelStrategy {
  public:
    virtual void aging(Administrator &ad);
    virtual void mating(Administrator &ad);
    virtual void migrate(Administrator &ad);
    virtual void contact(Administrator &ad);
    virtual void infect(Administrator &ad);
    virtual void response(Administrator &ad);
    virtual void oneDay(Administrator &ad);
};

/*-----------------------------------------------------------------------------
 *  NonOverlappingPopulation 戦略
 *-----------------------------------------------------------------------------*/
class NonOverlappingPopulation : public __ModelStrategy {
  public:
    virtual void aging(Administrator &ad);
    virtual void mating(Administrator &ad);
    virtual void migrate(Administrator &ad);
    virtual void contact(Administrator &ad);
    virtual void infect(Administrator &ad);
    virtual void response(Administrator &ad);
    virtual void oneDay(Administrator &ad);
};

#endif
