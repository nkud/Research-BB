/*
 * =====================================================================================
 *
 *       Filename:  AgentManager.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU
 *
 * =====================================================================================
 */

#include "Global.h"
#include "Agent.h"
#include "AgentManager.h"
#include "AgentCounter.h"
#include "Landscape.h"
#include "Function.h"

#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)

int AgentManager :: numIsIncubation() const {
  int ret = 0;
  EACH( it_a, agents_ ) {
    if( (*it_a)->isIncubation() ) {
      ret++;
    }
  }
  return ret;
}
int AgentManager :: numIsCrisis() const {
  int ret = 0;
  EACH( it_a, agents_ ) {
    if( (*it_a)->isCrisis() ) {
      ret++;
    }
  }
  return ret;
}

/*-----------------------------------------------------------------------------
 *  AgentManager
 *-----------------------------------------------------------------------------*/
AgentManager :: AgentManager( VECTOR( Agent * ) &agents ) :
  agents_( agents )
{
  LOG("init AgentManager");
}

/*-----------------------------------------------------------------------------
 *  initAgent
 *-----------------------------------------------------------------------------*/
void AgentManager :: initAgent( __MovingStrategy *ms, __ChildBirthStrategy *cbs, int len, int num )
{
  FOR( i, num ) {                                                    /* num のだけ */
    agents_.push_back( new Agent( ms, cbs, len ) );                  /* 新しくエージェントを加える */
  }
  // マップに配置する
  Landscape::Instance().clearAgentMap();                             /* エージェントの位置をリセット */
  int tx, ty;                                                        /* 移動させる場所 */

  ITERATOR(Agent *) it_a = getAgentIteratorBegin();                  /* エージェントの先頭から */
  while( it_a != getAgentIteratorEnd() ) {                           /* 末尾まで */
    tx = rand_interval_int( 0, WIDTH-1 );                            /* ランダムに設定 */
    ty = rand_interval_int( 0, WIDTH-1 );
    (*it_a)->setX( tx );                                             /* 配置 */
    (*it_a)->setY( ty );

    assert( 0 <= tx && tx <= WIDTH-1 );                              /* 土地の外ならエラー */
    assert( 0 <= ty && ty <= WIDTH-1 );

    Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a ); /* エージェントを登録 */
    it_a++;
  }
}

/*-----------------------------------------------------------------------------
 *  initInfectAgentInRatio( Virus &, double )
 *-----------------------------------------------------------------------------*/
void AgentManager :: initInfectAgentInRatio( Virus &v, double r ) {
  static int infected_from = 0;                                      /* ０番目のエージェントから順に感染させる */
  int infected_to;
  infected_to = infected_from + (int)( getAgentSize() * r );
  REP( i, infected_from, infected_to ) {
    agents_[ i%getAgentSize() ]->infection( v );
  }
  infected_from = ( infected_to + 1 ) % getAgentSize();              /* 次の感染は、感染した次のエージェントから始まる */
}
/*-----------------------------------------------------------------------------
 *  migrate()
 *-----------------------------------------------------------------------------*/
void AgentManager :: migrate()
{
  Landscape::Instance().clearAgentMap();                             /* エージェントの位置をリセットして */
  ITERATOR(Agent *) it_a = getAgentIteratorBegin();                  /* エージェントの先頭から */
  while( it_a != getAgentIteratorEnd() ) {                           /* 末尾まで */
    (*it_a)->move();                                                 /* 移動させる */
    Landscape::Instance().putAgentOnMap( **it_a );                   /* 土地からはみ出てたら戻す */
    Landscape::Instance().registAgent( (*it_a)->getX(), (*it_a)->getY(), **it_a );                   /* エージェントを登録 */
    it_a++;                                                          /* 次のエージェントへ */
  }
}
/*-----------------------------------------------------------------------------
 *  contact()
 *-----------------------------------------------------------------------------*/
void AgentManager :: contact()
{
  int ax, ay;
  int tx, ty;

  ITERATOR(Agent *) it_myself = getAgentIteratorBegin();             /* エージェントの先頭から */
  while( it_myself != getAgentIteratorEnd() ) {                      /* 末尾まで */
//    if( (*it_myself)->numHoldingVirus() <= 0 ) {
//      it_myself++;
//      continue;                                                      /* 健康ならスキップ */
//    }
    if( (*it_myself)->getImmuneSystem()->getOnSetVirusListSize() < 1 ) { /* 発症していなければ */
      it_myself++;                                                   /* 次のエージェントへ */
      continue;
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
        Landscape::Instance().putBackOnMap( tx, ty );

        ITERATOR(Agent *) it = Landscape::Instance().getAgentIteratorBeginAt( tx, ty );
        while( it != Landscape::Instance().getAgentIteratorEndAt( tx, ty ) )
        {                                                            /* その位置にいる人全員に */
          Virus *v =                                                 /* ランダムに保持ウイルスから選んで */
            (*it_myself)->getImmuneSystem()->getOnSetVirusAt( rand_array((*it_myself)->getImmuneSystem()->getOnSetVirusListSize()) );

          if( v->getRate() > rand_interval_double(0,1) )
          {                                                          /* ウイルス特有の感染確率で */
            (*it)->getImmuneSystem()->pushStandByVirus( v );         /* 待機ウイルスにする */
          }
          it++;                                                      /* 着目をその位置の次にいる人 */

          AgentCounter::Instance().countUpContact();                 /* モニタリング */
        }
      }
    }
    it_myself++;
  }
}
void AgentManager :: infect()
{
  /*-----------------------------------------------------------------------------
   *  感染の処理
   *-----------------------------------------------------------------------------*/
  ITERATOR(Virus *) itt;
  Virus *v;
  int n;
  int infection_count;                                               /* 同時感染数をカウント。最大値を越えないように */

  ITERATOR(Agent *) it_myself = getAgentIteratorBegin();
  while( it_myself != getAgentIteratorEnd() ) {
    if( (*it_myself)->getImmuneSystem()->hasNoStandByVirus() ) {     /* 待機ウイルスが無ければ */
      it_myself++;                                                   /* 次のエージェントに */
      continue;                                                      /* スキップ */
    } else {                                                         /* あれば */
      infection_count = 0;

      while( ! (*it_myself)->getImmuneSystem()->hasNoStandByVirus() ) { /* 待機ウイルスがなくなるまで */
        if( infection_count >= A_MAX_V_INFECTED_ONE_TERM ) {         /* もし最大同時感染数を越えそうなら */
          break;                                                     /* 次のエージェントへ */
        }

        n = rand_array( (*it_myself)->getImmuneSystem()->getStandByVirusListSize() ); /* ランダムに一個の */
        v = (*it_myself)->getImmuneSystem()->getStandByVirusAt( n ); /* ウイルスを選んで */
        if( (*it_myself)->infection( *v ) ) {                        /* 感染させたら */
          infection_count++;                                         /* カウントを増やす */
        } else {
          itt = (*it_myself)->getImmuneSystem()->getStandByVirusListIteratorBegin();         /* もし感染しなければ */
          while(n-->0) { itt++; }                                    /* そのウイルスを */
          itt = (*it_myself)->getImmuneSystem()->eraseStandByVirus( itt ); /* 待機ウイルスからはずして次のウイルス */
        }
      }
      (*it_myself)->getImmuneSystem()->clearStandByVirus();          /* 待機ウイルスをクリア */
    }
    it_myself++;                                                     /* 次のエージェントに */
  }
}
void AgentManager :: response()
{
  ITERATOR( Agent * ) it_a = getAgentIteratorBegin();                /* エージェントの先頭から */
  while( it_a != getAgentIteratorEnd() )                             /* 末尾まで */
  { 
    assert( (*it_a) != NULL );

    (*it_a)->response();                                             /* 免疫応答させる */

    bool flag = false;
    ITERATOR( Virus * ) it_v
      = (*it_a)->getImmuneSystem()->getVirusListIteratorBegin();     /* 先頭のウイルスデータから */
    while( it_v != (*it_a)->getImmuneSystem()->getVirusListIteratorEnd() ) /* 末尾まで */
    {
      if( (*it_v)->isLethalPeriod() ) {                              /* 感染期間が長すぎる */
        flag = true;                                                 /* ウイルスがあれば */
        break;
      }
      it_v++;
    }
    if( flag ) {
      // it_a = deleteAgent( it_a );                                    /* 生存配列から削除される */
      (*it_a)->rebirth();
    } else {
      it_a++;                                                        /* 次のエージェントへ */
    }
  }
}
void AgentManager :: aging()
{
  ITERATOR(Agent *) it_a = getAgentIteratorBegin();                  /* 先頭のエージェントから */
  while( it_a != getAgentIteratorEnd() ) {                           /* エージェントの末尾まで */

    (*it_a)->aging();                                                /* 老化させる */

    if( (*it_a)->getAge() > A_MAX_AGE ) {                            /* もし寿命をこえたら */
      it_a = deleteAgent( it_a );                                    /* 生存配列から削除される */
    } else {
      it_a++;                                                        /* 次のエージェントへ */
    }
  }
}
void AgentManager :: mating()
{
  /*-----------------------------------------------------------------------------
   *  交配・出産
   *-----------------------------------------------------------------------------*/
  int ax, ay;
  int tx, ty;

  VECTOR(Agent *) new_child_;                                        /* 新しく生まれるエージェント */

  ITERATOR(Agent *) it_myself = getAgentIteratorBegin();             /* エージェント配列の先頭から */
  while( it_myself != getAgentIteratorEnd() ) {                      /* 末尾まで */
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
        Landscape::Instance().putBackOnMap( tx, ty );                /* 土地からはみ出てたら土地の上に戻す */

        ITERATOR(Agent *) it_partner= Landscape::Instance().getAgentIteratorBeginAt( tx, ty );
        while( it_partner!= Landscape::Instance().getAgentIteratorEndAt( tx, ty ) )
        {                                                            /* 自分の近隣にいる人から */
          if( getAgentSize()+new_child_.size() >= A_MAX_NUM ) {      /* 最大エージェントをこえそうなら */
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

  ITERATOR(Agent *) it_a = getAgentIteratorBegin();                  /* エージェントの先頭 */
  while( it_a != getAgentIteratorEnd() ) {                           /* エージェント全員に対して */
    (*it_a)->resetGiveBirth();                                       /* 未出産に戻す */
    it_a++;                                                          /* 次のエージェント */
  }
  LOG( new_child_.size() );
  ITERATOR( Agent * ) it_child = new_child_.begin();                 /* 新しく誕生したエージェントを */
  while( it_child != new_child_.end() ) {
    agents_.push_back( *it_child );                                  /* エージェント配列に一斉に加える */
    Landscape::Instance().registAgent( (*it_child)->getX(), (*it_child)->getY(), **it_child ); /* 土地に配置 */
    it_child++;                                                      /* 次のエージェントに */
  }
  new_child_.clear();                                                /* 新しく誕生したエージェントの配列をクリア */
}

/*-----------------------------------------------------------------------------
 *  deleteAgent
 *-----------------------------------------------------------------------------*/
ITERATOR(Agent *) AgentManager :: deleteAgent( ITERATOR(Agent *) &it )
{
  assert( (*it) != NULL );                                           /* メモリが無ければエラー */

  Landscape::Instance().removeAgent( (*it)->getX(), (*it)->getY(), **it );     /* 土地から削除 */

  delete( *it );                                                     /* メモリ領域を削除 */
  ITERATOR(Agent *) next = agents_.erase( it );                      /* 配列から削除 */

  return next;
}

void AgentManager :: printInitInfo() const {
  std::cout << "\nNUM_A:\t\t" << getAgentSize() << std::endl;
  std::cout << "TAG_LEN_A:\t" << A_DEFAULT_LEN << std::endl;
}
/*-----------------------------------------------------------------------------
 *  numHasVirus
 *-----------------------------------------------------------------------------*/
int AgentManager :: numHasVirus() {
  int ret = 0;
  C_ITERATOR(Agent *) it_a = getAgentIteratorBegin();
  while( it_a != getAgentIteratorEnd() ) {                           /* エージェント全員に対して */
    if( (*it_a)->hasVirus() ) {                                      /* 感染していれば */
      ret++;                                                         /* インクリメント */
    }
    it_a++;
  }
  return ret;                                                        /* v の感染者数を返す */
}
