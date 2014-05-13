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

class Virus;
class Administrator;
class __MovingStrategy;
class __ChildBirthStrategy;

/* =====================================================================================
 *        Class:  __ModelStrategy
 *  Description:  数理モデルの戦略
 *  TODO: why need setting pure virtual??
 * ================================================================================== */
class __ModelStrategy {
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・セッタ
     *-----------------------------------------------------------------------------*/
    __ModelStrategy( Administrator * );
    void setAdministrator( Administrator * );
    /*-----------------------------------------------------------------------------
     *  初期化
     *-----------------------------------------------------------------------------*/
    virtual void initAgent( __MovingStrategy *, __ChildBirthStrategy *, int, int );
    virtual void initVirus();
    virtual void initVirus( Virus * );
    /*-----------------------------------------------------------------------------
     *  各フェイズ
     *-----------------------------------------------------------------------------*/
    virtual void migrate();                                          /* 移動 */

    virtual void contact();                                          /* 接触 */
    virtual void infect();                                           /* 感染 */
    virtual void response();                                         /* 免疫応答 */

    virtual void aging();                                            /* 老化 */
    virtual void mating();                                           /* 交配 */
    /*-----------------------------------------------------------------------------
     *  すべてプロセスを実行
     *-----------------------------------------------------------------------------*/
    virtual void executeOneDay();

  protected:                                                         /* XXX: あまりよくない */
    Administrator *ad_;
};

#endif
