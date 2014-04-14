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
void Monitor :: resetAll()
{
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

void Monitor :: setTerm( int t ) {
    term_ = t;
}
int Monitor :: getTerm() const {
    return term_;
}
