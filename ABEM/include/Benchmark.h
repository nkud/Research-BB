/*
 * =====================================================================================
 *
 *       Filename:  Benchmark.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/18/2013 11:04:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ___BENCHMARK
#define ___BENCHMARK

#include <sys/time.h>

/*
 * =====================================================================================
 *        Class:  Benchmark
 *  Description:  ベンチマーク
 *                シングルトンパターン
 * =====================================================================================
 */
class Benchmark {
    public:
        static Benchmark& Instance()                                /* インスタンスを返す */
        { static Benchmark singleton; return singleton; }

        void startTimer()                                           /* 計測開始する */
        { gettimeofday(&tv_, NULL); start_ = tv_.tv_sec + tv_.tv_usec * 1e-6; }

        void stopTimer()                                            /* 計測終了する */
        { gettimeofday(&tv_, NULL); end_ = tv_.tv_sec + tv_.tv_usec * 1e-6; }

        double getTime() const                                      /* 計測時間を返す */
        { return end_-start_; }

        void printTime() const                                      /* 計測時間を表示 */
        { std::cout << "[ time ]: " << end_ - start_ << " sec" << std::endl; }

        void printElapsedTime() {                                     /* 計測時間を表示 */
        gettimeofday(&tv_, NULL);
        double now = tv_.tv_sec + tv_.tv_usec * 1e-6;
        std::cout << "[ elapsed time (sec) ]: " << now - start_ << std::endl; }

    private:
        Benchmark() {}

        struct timeval tv_;                                          /* 計測開始時間 */
        double start_;                                               /* 計測終了時間 */
        double end_;
};

#endif