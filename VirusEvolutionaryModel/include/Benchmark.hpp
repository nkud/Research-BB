#ifndef ___BENCHMARK_HPP
#define ___BENCHMARK_HPP

#include <sys/time.h>

/**
 * @brief ベンチマーク
 *
 * シングルトンパターン
 */
class Benchmark {
  public:
    static Benchmark& Instance()                 /// インスタンスを返す
    { static Benchmark singleton; return singleton; }

    void startTimer()                            /// 計測開始する 
    { gettimeofday(&tv_, NULL); start_ = tv_.tv_sec + tv_.tv_usec * 1e-6; }

    void stopTimer()                             /// 計測終了する 
    { gettimeofday(&tv_, NULL); end_ = tv_.tv_sec + tv_.tv_usec * 1e-6; }

    double getTime() const                       /// 計測時間を返す
    { return end_-start_; }

    void printTime() const                       /// 計測時間を表示 
    { std::cout << "[ time ]: " << end_ - start_ << " sec" << std::endl; }

    double getElapsedTime()                      /// 経過時間を取得
    {
      gettimeofday(&tv_, NULL);
      double now = tv_.tv_sec + tv_.tv_usec * 1e-6;
      return now - start_;
    }

    void printElapsedTime()                      /// 計測時間を表示 
    { std::cout << "[ elapsed time (sec) ]: " << getElapsedTime() << std::endl; }

  private:
    Benchmark() {}

    struct timeval tv_;                          /// 時間構造体
    double start_;                               /// 計測開始時間 
    double end_;                                 /// 計算終了時間
};

#endif
