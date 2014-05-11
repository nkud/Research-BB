/*
 * =====================================================================================
 *
 *       Filename:  Benchmark.cpp
 *
 *    Description:  ベンチマーク
 *                  only unix
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include <iostream>
#include <sys/time.h>

#include "Benchmark.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Benchmark :: *
 * Description:  実行時間を表示( unix only )
 *--------------------------------------------------------------------------------------
 */
Benchmark& Benchmark :: Instance() {
    static Benchmark bm;
    return bm;
}
void Benchmark :: startTimer() {
    gettimeofday(&tv_, NULL);
    start_ = tv_.tv_sec + tv_.tv_usec * 1e-6;
}
void Benchmark :: stopTimer() {
    gettimeofday(&tv_, NULL);
    end_ = tv_.tv_sec + tv_.tv_usec * 1e-6;
}
double Benchmark :: getTime() const {
    return end_ - start_;
}
void Benchmark :: printTime() const {
    std::cout << "[ time ]: " << end_ - start_ << " sec" << std::endl;
}
void Benchmark :: printElapsedTime() {
    gettimeofday(&tv_, NULL);
    double now = tv_.tv_sec + tv_.tv_usec * 1e-6;
    std::cout << "[ elapsed time ]: " << now - start_ << " sec" << std::endl;
}
