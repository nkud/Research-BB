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
#include <sys/time.h>

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


/*
 * =====================================================================================
 *        Class:  Benchmark
 *  Description:  ベンチマーク
 *                シングルトンパターン
 * =====================================================================================
 */
class Benchmark {
    private:
        Benchmark() {}

        struct timeval tv_;
        double start_;
        double end_;
    public:
        static Benchmark& Instance();           /* インスタンスを返す */

        void startTimer();                           /* 計測開始する */
        void stopTimer();                            /* 計測終了する */

        double getTime() const;                              /* 計測時間を返す */
        void printTime() const;                              /* 計測時間を表示 */
        void printElapsedTime();                              /* 計測時間を表示 */
};

#endif
