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
     *  初期化
     *-----------------------------------------------------------------------------*/
//    virtual void initAgent();
    void setAdministrator(Administrator *ad) { ad_ = ad; }
    void initAgent();
    void initVirus();
    /*-----------------------------------------------------------------------------
     *  各フェイズ
     *-----------------------------------------------------------------------------*/
    virtual void aging() = 0;
    virtual void mating() = 0;
    virtual void migrate() = 0;
    virtual void contact() = 0;
    virtual void infect() = 0;
    virtual void response();
    /*-----------------------------------------------------------------------------
     *  すべてプロセスを実行
     *-----------------------------------------------------------------------------*/
    virtual void oneDay();
  protected:                                                         /* XXX: あまりよくない */
    Administrator *ad_;
};

/*-----------------------------------------------------------------------------
 *  デフォルトの戦略
 *-----------------------------------------------------------------------------*/
class Default : public __ModelStrategy {
  public:
    virtual void aging();
    virtual void mating();
    virtual void migrate();
    virtual void contact();
    virtual void infect();
};

/*-----------------------------------------------------------------------------
 *  NonOverlappingPopulation 戦略
 *-----------------------------------------------------------------------------*/
class NonOverlappingPopulation : public __ModelStrategy {
  public:
    virtual void aging();
    virtual void mating();
    virtual void migrate();
    virtual void contact();
    virtual void infect();
    virtual void oneDay();
};

#endif
