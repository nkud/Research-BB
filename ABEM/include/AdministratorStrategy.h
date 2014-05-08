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
 *  TODO: why need setting pure virtual??
 * ================================================================================== */
class __ModelStrategy {
  public:
    /*-----------------------------------------------------------------------------
     *  初期化
     *-----------------------------------------------------------------------------*/
    void setAdministrator(Administrator *ad) { ad_ = ad; }
    virtual void initAgent();
    virtual void initVirus();
    /*-----------------------------------------------------------------------------
     *  各フェイズ
     *-----------------------------------------------------------------------------*/
    virtual void migrate();

    virtual void contact();
    virtual void infect();
    virtual void response();

    virtual void aging();
    virtual void mating();
    /*-----------------------------------------------------------------------------
     *  すべてプロセスを実行
     *-----------------------------------------------------------------------------*/
//    virtual void oneDay();

  protected:                                                         /* XXX: あまりよくない */
    Administrator *ad_;
};

/*-----------------------------------------------------------------------------
 *  デフォルト 戦略
 *-----------------------------------------------------------------------------*/
class Default : public __ModelStrategy {
  public:
    virtual void aging();
    virtual void mating();
};

/*-----------------------------------------------------------------------------
 *  NonOverlappingPopulation 戦略
 *-----------------------------------------------------------------------------*/
class NonOverlappingPopulation : public __ModelStrategy {
  public:
    virtual void initAgent();

    virtual void aging();
    virtual void mating();
//    virtual void oneDay();
};


/*-----------------------------------------------------------------------------
 *  OverlappingPopulation 戦略
 *-----------------------------------------------------------------------------*/
class OverlappingPopulation : public __ModelStrategy {
    public:
};

#endif
