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

/*
 * =====================================================================================
 *        Class:  Monitor
 *  Description:  シングルトンパターン
 * =====================================================================================
 */
class Monitor {
    private:
        Monitor(): count_infection_contact_( 0 ) {};                              /* コンストラクタ */
    public:
        static Monitor& getInstance();

        int count_infection_contact_;

        void resetAll();                 /* 値をすべてリセット */
};

#endif
