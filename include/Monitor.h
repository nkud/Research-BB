/*
 * =====================================================================================
 *
 *       Filename:  Monitor.h
 *
 *    Description:  モニター
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___MONITOR
#define ___MONITOR

#include <map>
#include <fstream>

#ifdef __unix__
#include <sys/time.h>
#endif

class __TagInterface;

/*
 * =====================================================================================
 *        Class:  Monitor
 *  Description:  ( シングルトンパターン )
 * =====================================================================================
 */
class Monitor {
    private:
        Monitor(): term_(0), num_contact_(0) { }                     /* コンストラクタ */

        int num_contact_;                                            /* 接触回数 */
        std::map<__TagInterface *, int> num_infection_contact_;      /* 感染させた接触回数 */

        int term_;

    public:
        static Monitor& Instance();                                  /* インスタンスを返す */

        /* ゲッタ */
        int getContactNum() const;                                   /* 接触回数を返す */
        int getInfectionContactNum( __TagInterface * );              /* 指定のウイルスの感染接触回数を返す */

        /* カウント */
        void countUpContact();                                       /* 接触しした回数 */
        void countUpInfectionContact( __TagInterface * );            /* 感染のために接触してあるウイルスに感染した回数 */

        void setTerm();                                              /* 期間を取得 */
        void getTerm();                                              /* 期間を返す */

        void resetAll();                                             /* 値をすべてリセット */
};

#ifdef __unix__
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

        struct timeval tv_;                                          /* 計測開始時間 */
        double start_;                                               /* 計測終了時間 */
        double end_;
    public:
        static Benchmark& Instance();                                /* インスタンスを返す */

        void startTimer();                                           /* 計測開始する */
        void stopTimer();                                            /* 計測終了する */

        double getTime() const;                                      /* 計測時間を返す */
        void printTime() const;                                      /* 計測時間を表示 */
        void printElapsedTime();                                     /* 計測時間を表示 */
};
#endif

#endif
