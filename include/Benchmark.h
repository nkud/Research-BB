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

/*
 * =====================================================================================
 *        Class:  Benchmark
 *  Description:  ベンチマーク
 *                シングルトンパターン
 * =====================================================================================
 */
class Benchmark {
    public:
        static Benchmark& Instance();                                /* インスタンスを返す */

        void startTimer();                                           /* 計測開始する */
        void stopTimer();                                            /* 計測終了する */

        double getTime() const;                                      /* 計測時間を返す */
        void printTime() const;                                      /* 計測時間を表示 */
        void printElapsedTime();                                     /* 計測時間を表示 */

    private:
        Benchmark() {}

        struct timeval tv_;                                          /* 計測開始時間 */
        double start_;                                               /* 計測終了時間 */
        double end_;
};
