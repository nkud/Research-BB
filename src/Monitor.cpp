/*
 * =====================================================================================
 *
 *       Filename:  Monitor.cpp
 *
 *    Description:  モニター、ベンチマーク
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Monitor.h"
#include "Global.h"
#include "Agent.h"
#include "Virus.h"

#include <fstream>
#include <iostream>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: *
 * Description:  ゲッタ
 *--------------------------------------------------------------------------------------
 */
int Monitor :: getContactNum() const { return num_contact_; }        /* 接触回数を返す*/
int Monitor :: getInfectionContactNum( __TagInterface *t ) {
    return num_infection_contact_[ t ];                              /* 感染接触回数を返す */
}
Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;                                                 /* インスタンスを返す */
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: resetAll()
 * Description:  カウントをリセット
 *--------------------------------------------------------------------------------------
 */
void Monitor :: resetAll() {
    num_contact_ = 0;                                                /* 接触回数をリセット */

    num_infection_contact_.clear();                                  /* 感染接触回数をリセット */
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: countUp *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Monitor :: countUpInfectionContact( __TagInterface *pv ) {
    num_infection_contact_[ pv ]++;                                  /* 指定のウイルスの感染接触回数をカウント */
}
void Monitor :: countUpContact() { num_contact_++; }                 /* 接触回数をカウント */

#ifdef __unix__
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
#endif

