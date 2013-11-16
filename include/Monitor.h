/*
 * =====================================================================================
 *
 *       Filename:  Monitor.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___MONITOR
#define ___MONITOR

#include <map>

class __TagInterface;

/*
 * =====================================================================================
 *        Class:  Monitor
 *  Description:  ( シングルトンパターン )
 * =====================================================================================
 */
class Monitor {
    private:
        Monitor() {}                                       /* コンストラクタ */

        int num_contact_;                                  /* 接触回数 */
        std::map<__TagInterface *, int> num_infection_contact_; /* 感染させた接触回数 */

    public:
        static Monitor& Instance();                        /* インスタンスを返す */

        /* ゲッタ */
        int getContactNum() const;
        int getInfectionContactNum( __TagInterface * );
        int getHasImmunityAllVirusNum() const;
        int getInfectOthersNum() const;

        /* カウント */
        void countUpContact();                             /* 接触しした回数 */
        void countUpInfectionContact( __TagInterface * );  /* 感染のために接触してあるウイルスに感染した回数 */

        void resetAll();                                   /* 値をすべてリセット */

        void generatePlotScript();
};

#endif
