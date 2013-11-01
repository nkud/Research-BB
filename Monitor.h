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
#define ___MONITOr

/*
 * =====================================================================================
 *        Class:  Monitor
 *  Description:  ( シングルトンパターン )
 * =====================================================================================
 */
class Monitor {
    private:
        Monitor():
            num_infection_contact_( 0 ) {};                              /* コンストラクタ */
    public:
        static Monitor& Instance();

        int num_infection_contact_;
        int num_contact_;
        int num_has_immunity_all_virus_;
        int num_infect_others;

        void countUpInfectionContact();         /* 感染のために接触した回数 */
        void countUpContact();                  /* 接触しした回数 */
        void countUpHasImmunityAllVirus();      /* すべてのウイルスに対して免疫獲得している人の数 */
        void countUpInfectOthers();             /* 他人に感染させた回数 */

        void resetAll();                        /* 値をすべてリセット */
        void generatePlotScript();
};

#endif
