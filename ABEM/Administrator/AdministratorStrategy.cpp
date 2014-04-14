/* =============================================================================
 *
 *       Filename:  AdministratorStrategy.cpp
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * ========================================================================== */

#include "Administrator.h"
#include "Landscape.h"
#include "Agent.h"
#include "AdministratorStrategy.h"
#include "Monitor.h"
#include "Function.h"

#include <string>

/*-----------------------------------------------------------------------------
 *
 *  基底クラス
 *
 *-----------------------------------------------------------------------------*/
void __ModelStrategy :: oneDay() {
  /*-----------------------------------------------------------------------------
   *  エージェントの一日の行動
   *    1. 老化
   *    2. 交配・出産
   *    3. 移動
   *    4. 近隣に接触
   *    5. 感染
   *    6. 免疫応答
   *-----------------------------------------------------------------------------*/
#ifdef AGING_AGENT
  ad_->agingAgent();                                                 /* 老化する */
#endif
#ifdef MATING_AGENT
  ad_->matingAgant();                                                /* 交配、出産する */
#endif
  ad_->moveAgent();                                                  /* 移動する */
  ad_->contactAgent();                                               /* 近隣に接触する */
  ad_->infectAgent();                                                /* 待機ウイルスを感染させる */
  ad_->responseAgent();                                              /* 免疫応答（タグフリップ） */
}
void
__ModelStrategy :: response() {
  /*-----------------------------------------------------------------------------
   *  免疫応答
   *-----------------------------------------------------------------------------*/
  ITERATOR( Agent * ) it_a = ad_->getAgentIteratorBegin();
  while( it_a != ad_->getAgentIteratorEnd() ) {
    (*it_a)->response();                                             /* 免疫応答 */
    it_a++;
  }

}
void
__ModelStrategy :: initAgent() {
  /*-----------------------------------------------------------------------------
   *  エージェントを初期化する
   *-----------------------------------------------------------------------------*/
  //  Relocate *relocate = new Relocate;
  RandomWalk *random_walk = new RandomWalk( 1 );
  //    CoupleTag *couple_tag = new CoupleTag;
  //  InheritanceLen *inh_len = new InheritanceLen;
  Relocate *relocate = new Relocate;
  FOR( i, A_INIT_NUM ) {                                             /* 初期エージェントの数だけ */
    ad_->agent()->push_back(
        new Agent( relocate, A_TAG_LEN ) );                          /* ランダムウォーク */
  }
}
void
__ModelStrategy :: initVirus() {
  /*-----------------------------------------------------------------------------
   *  ウイルスを初期化する
   *-----------------------------------------------------------------------------*/
  // XXX
  //                                   1234567890123456789
  ad_->virus()->push_back( new Virus( V_TAG_0, new Normal ) );        /* 通常ウイルスを追加 */
  ad_->virus()->push_back( new Virus( V_TAG_1, new Normal ) );       /* 通常ウイルスを追加 */
  //  ad_->virus()->push_back( new Virus( 15, new Normal ) );          /* 通常ウイルスを追加 */
  //  ad_->virus()->push_back( new Virus( 15, new Normal ) );          /* 通常ウイルスを追加 */
  //  virus.push_back( new Virus( 20, new Fixed(0) ) );                /* 固定ウイルスを追加 */
  //  virus.push_back( new Virus( 10, new Fixed(20) ) );               /* 固定ウイルスを追加 */
}
void __ModelStrategy :: migrate() {
  /*-----------------------------------------------------------------------------
   *  移動
   *-----------------------------------------------------------------------------*/
  (ad_->landscape())->clearAgentMap();                               /* エージェントの位置をリセットして */
  ITERATOR(Agent *) it_a = ad_->getAgentIteratorBegin();             /* エージェントの先頭から */
  while( it_a != ad_->getAgentIteratorEnd() ) {                      /* 末尾まで */
    (*it_a)->move();                                                 /* 移動させる */
    ad_->landscape()->putAgentOnMap( **it_a );                       /* 土地からはみ出てたら戻す */
    ad_->landscape()->registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a );                   /* エージェントを登録 */
    it_a++;                                                          /* 次のエージェントへ */
  }
}
void
__ModelStrategy :: infect() {
  /*-----------------------------------------------------------------------------
   *  感染の処理
   *-----------------------------------------------------------------------------*/
  ITERATOR(Virus *) itt;
  Virus *tv;
  int n;
  int infection_count;                                               /* 同時感染数をカウント。最大値を越えないように */

  ITERATOR(Agent *) it_myself = ad_->getAgentIteratorBegin();
  while( it_myself != ad_->getAgentIteratorEnd() ) {
    if( (*it_myself)->hasNoStandByVirus() ) {                        /* 待機ウイルスが無ければ */
      it_myself++;                                                   /* 次のエージェントに */
      continue;                                                      /* スキップ */
    } else {                                                         /* あれば */
      infection_count = 0;

      while( ! (*it_myself)->hasNoStandByVirus() ) {                 /* 待機ウイルスがなくなるまで */
        if( infection_count >= A_MAX_V_INFECTED_ONE_TERM ) {         /* もし最大同時感染数を越えそうなら */
          break;                                                     /* 次のエージェントへ */
        }

        n = rand_array( (*it_myself)->getStandByListSize() );        /* ランダムに一個の */
        tv = (*it_myself)->getStandByVirusAt( n );                   /* ウイルスを選んで */
        if( (*it_myself)->infection( *tv ) ) {                       /* 感染させたら */
          infection_count++;                                         /* カウントを増やす */
        } else {
          itt = (*it_myself)->getStandByListIteratorBegin();         /* もし感染しなければ */
          while(n-->0) { itt++; }                                    /* そのウイルスを */
          (*it_myself)->eraseStandByVirus( itt );                    /* 待機ウイルスからはずして次のウイルス */
        }
      }
      (*it_myself)->clearStandByVirus();                             /* 待機ウイルスをクリア */
    }
    it_myself++;                                                     /* 次のエージェントに */
  }
}
void
__ModelStrategy :: contact() {
  /*-----------------------------------------------------------------------------
   *  接触
   *-----------------------------------------------------------------------------*/
  int ax, ay;
  int tx, ty;

  ITERATOR(Agent *) it_myself = ad_->getAgentIteratorBegin();          /* エージェントの先頭から */
  while( it_myself != ad_->getAgentIteratorEnd() ) {                   /* 末尾まで */
    if( (*it_myself)->numHoldingVirus() <= 0 ) {
      it_myself++;
      continue;                                                      /* 健康ならスキップ */
    }
    ax = (*it_myself)->getX();                                       /* 感染者自身の位置 */
    ay = (*it_myself)->getY();

    REP( i, -1, 1 ) {                                                /* 自分の縦・横・自マスに感染させる（計５マス） */
      REP( j, -1, 1 ) {
#ifdef NO_DIAGONAL
        if( i*j != 0 ) {
          continue;                                                  /* 斜めは入れない */
        }
#endif
        tx = ax + i;
        ty = ay + j;
        ad_->landscape()->putBackOnMap( tx, ty );

        ITERATOR(Agent *) it = ad_->landscape()->getAgentIteratorBeginAt( tx, ty );
        while( it != ad_->landscape()->getAgentIteratorEndAt( tx, ty ) )
        {                                                            /* その位置にいる人全員に */
          VirusData *tvdata =                                        /* ランダムに保持ウイルスから選んで */
            (*it_myself)->getVirusDataAt( rand_array((*it_myself)->getVirusListSize()) );

          if( tvdata->v_->getRate() > rand_interval_double(0,1) )
          {                                                          /* ウイルス特有の感染確率で */
            (*it)->pushStandByVirus( tvdata->v_ );                   /* 待機ウイルスにする */
          }
          it++;                                                      /* 着目をその位置の次にいる人 */

          Monitor::Instance().countUpContact();                      /* モニタリング */
        }
      }
    }
    it_myself++;
  }
}
void
__ModelStrategy :: mating() {
  // no process
}
void
__ModelStrategy :: aging() {
  // no process
}
/*-----------------------------------------------------------------------------
 *
 *  デフォルト
 *
 *-----------------------------------------------------------------------------*/
void
Default :: mating() {
  /*-----------------------------------------------------------------------------
   *  交配・出産
   *-----------------------------------------------------------------------------*/
  int ax, ay;
  int tx, ty;

  VECTOR(Agent *) new_child_;                                        /* 新しく生まれるエージェント */

  ITERATOR(Agent *) it_myself = ad_->getAgentIteratorBegin();          /* エージェント配列の先頭から */
  while( it_myself != ad_->getAgentIteratorEnd() ) {                   /* 末尾まで */
    ax = (*it_myself)->getX();                                       /* 着目エージェントの位置 */
    ay = (*it_myself)->getY();

    if( (*it_myself)->hasAlreadyGiveBirth() ) {                      /* 既に出産済なら */
      it_myself++;
      continue;                                                      /* スキップ */
    }

    REP( i, -1, 1 )
    {                                                                /* 自分の近隣から異性を探す */
      REP( j, -1, 1 )
      {
        if( (*it_myself)->hasAlreadyGiveBirth() ) {                  /* 既に出産済なら */
          goto NEXT_AGENT;                                           /* スキップ */
        }

#ifdef NO_DIAGONAL
        if( i*j != 0 ) {
          continue;                                                  /* 斜めは入れない */
        }
#endif
        tx = ax + i;
        ty = ay + j;
        ad_->landscape()->putBackOnMap( tx, ty );                      /* 土地からはみ出てたら土地の上に戻す */

        ITERATOR(Agent *) it_partner= ad_->landscape()->getAgentIteratorBeginAt( tx, ty );
        while( it_partner!= ad_->landscape()->getAgentIteratorEndAt( tx, ty ) )
        {                                                            /* 自分の近隣にいる人から */
          if( ad_->getAgentSize()+new_child_.size() >= A_MAX_NUM ) {   /* 最大エージェントをこえそうなら */
            break;                                                   /* 終了 */
          }
          if( isOppositeSex( *(*it_myself), **it_partner) &&         /* 異性かつ */
              (*it_myself)->hasAbilityToChildbirth() &&
              (*it_partner)->hasAbilityToChildbirth() &&
              !(*it_myself)->hasAlreadyGiveBirth() &&                /* 未出産ならば */
              !(*it_partner)->hasAlreadyGiveBirth())
          {
            if( A_BIRTH_RATE > rand_interval_double(0, 1) )          /* 出産確率で */
            {
              new_child_.push_back( (**it_myself).childBirthWith(**it_partner) ); /* 新しい子供を誕生させる */
            }
            (*it_partner)->setGiveBirth();                           /* パートナーと自分を */
            (*it_myself)->setGiveBirth();                            /* 出産済にする */
          }                                                          /* XXX: パートナーを探すエージェントのランダム性 */
          it_partner++;                                              /* パートナーをその位置の次にいる人に移す */
        }
      }
    }
NEXT_AGENT:                                                          /* => 出産終了 */
    it_myself++;
  }

  ITERATOR(Agent *) it_a = ad_->getAgentIteratorBegin();               /* エージェントの先頭 */
  while( it_a != ad_->getAgentIteratorEnd() ) {                        /* エージェント全員に対して */
    (*it_a)->resetGiveBirth();                                       /* 未出産に戻す */
    it_a++;                                                          /* 次のエージェント */
  }
  LOG( new_child_.size() );
  ITERATOR( Agent * ) it_child = new_child_.begin();                 /* 新しく誕生したエージェントを */
  while( it_child != new_child_.end() ) {
    ad_->agent()->push_back( *it_child );                              /* エージェント配列に一斉に加える */
    ad_->landscape()->registAgent( (*it_child)->getX(), (*it_child)->getY(), **it_child ); /* 土地に配置 */
    it_child++;                                                      /* 次のエージェントに */
  }
  new_child_.clear();                                                /* 新しく誕生したエージェントの配列をクリア */
}
void
Default :: aging() {
  /*-----------------------------------------------------------------------------
   *  老化
   *-----------------------------------------------------------------------------*/
  ITERATOR(Agent *) it = ad_->getAgentIteratorBegin();                 /* 先頭のエージェントから */
  while( it != ad_->getAgentIteratorEnd() ) {                          /* エージェントの末尾まで */

    (*it)->aging();                                                  /* 老化させる */

    if( (*it)->getAge() > A_MAX_AGE ) {                              /* もし寿命をこえたら */
      ad_->deleteAgent( it );                                          /* 生存配列から削除される */
    } else {
      it++;                                                          /* 次のエージェントへ */
    }
  }
}
/*-----------------------------------------------------------------------------
 *
 *  NonOverlappingPopulation 戦略
 *
 *-----------------------------------------------------------------------------*/
void NonOverlappingPopulation :: initAgent() {
  RandomWalk *random_walk = new RandomWalk( 1 );
  Relocate *relocate = new Relocate;
  FOR( i, A_INIT_NUM ) {                                             /* 初期エージェントの数だけ */
    ad_->agent()->push_back(
        new Agent( random_walk, 20 ) );                                 /* ランダムウォーク */
  }
//  ITERATOR(Agent *) it = ad_->getAgentIteratorBegin();               /* 先頭のエージェントから */
//  while( it != ad_->getAgentIteratorEnd() ) {                        /* エージェントの末尾まで */
//    (*it)->setAge(0);
//    it++;
//  }
}

void
NonOverlappingPopulation :: oneDay() {
  ad_->agingAgent();                                                   /* 老化する */
  ad_->moveAgent();                                                    /* 移動する */

  ad_->contactAgent();                                                 /* 近隣に接触する */
  ad_->infectAgent();                                                  /* 待機ウイルスを感染させる */
  ad_->responseAgent();                                                /* 免疫応答（タグフリップ） */
}

void
NonOverlappingPopulation :: aging() {
  int die=0;
  ITERATOR(Agent *) it = ad_->getAgentIteratorBegin();               /* 先頭のエージェントから */
  while( it != ad_->getAgentIteratorEnd() ) {                        /* エージェントの末尾まで */
    (*it)->aging();                                                  /* 老化させる */
    if( (*it)->getAge() > A_MAX_AGE ) {                              /* もし寿命をこえたら */
      (*it)->resetParam();                                            /* 生まれ変わる */
      die++;
    }
    it++;                                                            /* 次のエージェントへ */
  }
  // 死亡人数を表示
  LOG(die);
}

void
NonOverlappingPopulation :: mating() {
  ITERATOR(Agent *) it_b = ad_->getAgentIteratorBegin();
  ITERATOR(Agent *) it_e = ad_->getAgentIteratorEnd();
  it_e--;
  while( it_b < it_e ) {
    (*it_b)->resetParam();
    (*it_e)->resetParam();
    it_b++;
    it_e--;
  }
  if(it_b==it_e) {
    (*it_b)->resetParam();
  }
}