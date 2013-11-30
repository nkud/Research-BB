/*
 * =====================================================================================
 *
 *       Filename:  Administrator.cpp
 *
 *    Description:  管理者
 *                  エージェント、ウイルス、土地を管理、統括する
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Global.h"
#include "Function.h"
#include "Administrator.h"
#include "Agent.h"
#include "Virus.h"
#include "Landscape.h"
#include "Monitor.h"

#include <vector>
#include <fstream>
#include <iostream>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: deleteAgent()
 * Description:  配列から指定のエージェントを削除
 *--------------------------------------------------------------------------------------
 */
ITERATOR(Agent *) Administrator :: deleteAgent( ITERATOR(Agent *) &it )
{
    landscape_->removeAgent( (*it)->getX(), (*it)->getY(), **it );   /* 土地から削除 */
    delete (*it);                                                    /* メモリ領域を削除 */
    agent_.erase( it );                                              /* エージェントの配列から削除 */

    return it;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: agingAgent()
 * Description:  老化させる
 *               寿命を越えたら、死亡処理をする
 *--------------------------------------------------------------------------------------
 */
void Administrator :: agingAgent()
{
    ITERATOR(Agent *) it = agent_.begin();                           /* 先頭のエージェントから */
    while( it != agent_.end() ) {                                    /* エージェントの末尾まで */

        (*it)->aging();                                              /* 老化させる */

        if( (*it)->getAge() > MAX_AGE ) {                            /* もし寿命をこえたら */
            deleteAgent( it );                                       /* 生存配列から削除される */
        } else {
            it++;                                                    /* 次のエージェントへ */
        }
    }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: matingAgant()
 * Description:  交配し、新たなエージェントを誕生させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: matingAgant() {
    int tx, ty;

    VECTOR(Agent *) new_child_;                                      /* 新しく生まれるエージェント */

    ITERATOR(Agent *) it_myself = agent_.begin();                    /* エージェント配列の先頭 */
    while( it_myself != agent_.end() ) {                             /* 末尾まで実行 */
        tx = (*it_myself)->getX();                                   /* 着目エージェントの位置 */
        ty = (*it_myself)->getY();

        if( (*it_myself)->hasAlreadyGiveBirth() ) {                  /* 既に出産済なら */
            it_myself++;
            continue;                                                /* スキップ */
        }

        REP( i, -1, 1 ) {                                            /* 自分の近隣から異性を探す */
            REP( j, -1, 1 ) {
#ifdef NO_DIAGONAL
                if( i*j != 0 ) {
                    continue;                                        /* 斜めは入れない */
                }
#endif
                if( ! (landscape_->isOnMap( tx+i, ty+j )) ) {
                    continue;                                        /* 土地からはみ出てたらスキップ */
                }

                ITERATOR(Agent *) it_partner= landscape_->getLandscapeIteratorBeginAt( tx+i, ty+j );
                while( it_partner!= landscape_->getLandscapeIteratorEndAt( tx+i, ty+j ) )
                {                                                    /* 自分の近隣にいる人から */
                    if( agent_.size()+new_child_.size() >= MAX_NUM_A ) { /* 最大エージェントをこえそうなら */
                        break;                                       /* 終了 */
                    }
                    if( isOppositeSex( *(*it_myself), **it_partner) &&      /* 異性かつ */
                            !(*it_partner)->hasAlreadyGiveBirth()) { /* 未出産ならば */
                        if( BIRTH_RATE > rand_interval_double(0, 1) ) {
                            new_child_.push_back( childbirth( *(*it_myself), **it_partner) ); /* 新しい子供を誕生させる */
                        }
                        (*it_partner)->setGiveBirth();               /* パートナーと自分を */
                        (*it_myself)->setGiveBirth();                /* 出産済にする */
                    }                                                /* XXX: パートナーを探すエージェントのランダム性 */
                    it_partner++;                                    /* パートナーをその位置の次にいる人に移す */
                }
            }
        }
        it_myself++;
    }
    ITERATOR(Agent *) it_a = agent_.begin();                         /* エージェントの先頭 */
    while( it_a != agent_.end() ) {                                  /* エージェント全員に対して */
        (*it_a)->resetGiveBirth();                                   /* 未出産に戻す */
        it_a++;                                                      /* 次のエージェント */
    }
    std::cout<<"[new child]: "<<new_child_.size()<<std::endl;
    ITERATOR( Agent * ) it_child = new_child_.begin();               /* 新しく誕生したエージェントを */
    while( it_child != new_child_.end() ) {
        agent_.push_back( *it_child );                               /* エージェント配列に一斉に加える */
        landscape_->registAgent( (*it_child)->getX(), (*it_child)->getY(), **it_child ); /* 土地に配置 */
        it_child++;                                                  /* 次のエージェントに */
    }
    new_child_.clear();                                              /* 新しく誕生したエージェントの配列をクリア */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: *
 * Description:  期間系の関数
 *--------------------------------------------------------------------------------------
 */
void Administrator :: incrementTerm() {
    term_++;                                                         /* 期間をインクリメント */
}
int Administrator :: getTerm() const {
    return term_;                                                    /* 現在の期間 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: Administrator( Agent *, Virus * )
 * Description:  コンストラクタ
 *--------------------------------------------------------------------------------------
 */
Administrator :: Administrator( VECTOR(Agent *) &a, Virus *v, Landscape *l ) :
    term_( 0 ),
    agent_( a ),
    virus_( v ),
    landscape_( l )
{
    agent_.reserve( MAX_NUM_A );                                     /* 最大エージェント数まで領域確保 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: getNumOfAgent()
 * Description:  現在の総エージェント数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: getNumOfAgent() const {
    return agent_.size();                                            /* 現在の総エージェント数 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasVirus( __TagInterface & )
 * Description:  現在の感染者数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasVirus( __TagInterface &v ) const {
    int ret = 0;
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {                                  /* エージェント全員に対して */
        if( (*it_a)->hasVirus( v ) ) {                               /* v に感染していれば */
            ret++;                                                   /* インクリメント */
        }
        it_a++;
    }
    return ret;                                                      /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasImmunity( __TagInterface & )
 * Description:  現在の免疫獲得者数数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasImmunity( __TagInterface &v ) const {
    int ret = 0;
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {                                  /* エージェント全員に対して */
        if ( (*it_a)->hasImmunity( v ) ) {                           /* v の免疫を獲得していれば*/
            ret++;                                                   /* インクリメント */
        }                                                                  
        it_a++;                                                            
    }                                                                      
    return ret;                                                      /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: responseAgent()
 * Description:  エージェント全員に対して免疫応答させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: responseAgent() {
    ITERATOR( Agent * ) it_a = agent_.begin();
    while( it_a != agent_.end() ) {
        (*it_a)->response();                                         /* 免疫応答 */
        it_a++;
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator:: relocateAgent()
 * Description:  エージェントをランダムに再配置
 *               １つのところに複数人数も許可
 *--------------------------------------------------------------------------------------
 */
void Administrator :: relocateAgent() {
    landscape_->clearAgentMap();                                     /* エージェントの位置をリセット */
    int tx, ty;                                                      /* 移動させる場所 */
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {
        tx = rand_interval_int( 0, WIDTH-1 );                        /* ランダムに設定 */
        ty = rand_interval_int( 0, WIDTH-1 );
        (*it_a)->setX( tx );                                         /* 配置 */
        (*it_a)->setY( ty );
        landscape_->registAgent( tx, ty, **it_a );                   /* エージェントを登録 */
        it_a++;
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: moveAgent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Administrator :: moveAgent() {
    landscape_->clearAgentMap();                                     /* エージェントの位置をリセット */
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {                                  /* エージェントの数だけ */
        int tx = rand_interval_int( -MOVE_DISTANCE, MOVE_DISTANCE ); /* 相対的に x を動かす量*/
        int ty = rand_interval_int( -MOVE_DISTANCE, MOVE_DISTANCE ); /* 相対的に y を動かす量 */
        int xx = tx + (*it_a)->getX();                               /* x 座標を設定 */
        int yy = ty + (*it_a)->getY();                               /* y 座標を設定 */
        if( ! landscape_->isOnMap( xx, yy ) ) {                      /* もし移動先が土地の上になっていなければ */
            landscape_->putBackOnMap( xx, yy );                      /* 土地の上に戻す */
        }
        (*it_a)->setX( xx );                                         /* 移動を実行 */
        (*it_a)->setY( yy );
        landscape_->registAgent( xx, yy, **it_a );                   /* エージェントを土地に登録 */
        it_a++;
    }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: contactAgent()
 * Description:  自分の縦横自マス（計５マス）に対して
 *               自分の保持ウイルスリストからランダムに１つ選び出し全員に感染させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: contactAgent() {

    int tx, ty;

    ITERATOR(Agent *) it_myself = agent_.begin();                    /* エージェントの先頭から */
    while( it_myself != agent_.end() ) {                             /* 末尾まで */
        if( (*it_myself)->numHoldingVirus() <= 0 ) {
            it_myself++;
            continue;                                                /* 健康ならスキップ */
        }
        tx = (*it_myself)->getX();                                   /* 感染者自身の位置 */
        ty = (*it_myself)->getY();

        REP( i, -1, 1 ) {                                            /* 自分の縦・横・自マスに感染させる（計５マス） */
            REP( j, -1, 1 ) {
#ifdef NO_DIAGONAL
                if( i*j != 0 ) {
                    continue;                                        /* 斜めは入れない */
                }
#endif
                if( ! (landscape_->isOnMap( tx+i, ty+j )) ) {
                    continue;                                        /* 土地からはみ出てたらスキップ */
                }
                ITERATOR(Agent *) it = landscape_->getLandscapeIteratorBeginAt( tx+i, ty+j );
                while( it != landscape_->getLandscapeIteratorEndAt( tx+i, ty+j ) )
                {                                                    /* その位置にいる人全員に */
                    VirusData *tvdata =                              /* ランダムに保持ウイルスから選んで */
                        (*it_myself)->getVirusDataAt( rand_array((*it_myself)->getVirusListSize()) );

                    if( tvdata->v_->getRate() > rand_interval_double(0,1) )
                    {                                                /* ウイルス特有の感染確率で */
                        (*it)->pushStandByVirus( tvdata->v_ );       /* 待機ウイルスにする */
                    }
                    it++;                                            /* 着目をその位置の次にいる人 */

                    Monitor::Instance().countUpContact();            /* モニタリング */
                }
            }
        }
        it_myself++;
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: infectAgent()
 * Description:  待機ウイルスを感染させる
 *               待機ウイルスの中からランダムに一個選び、感染する
 *--------------------------------------------------------------------------------------
 */
void Administrator :: infectAgent() {
    ITERATOR(Virus *) itt;
    Virus *tv;
    int n;
    int infection_count;                                             /* 同時感染数をカウント。最大値を越えないように */

    ITERATOR(Agent *) it_myself = agent_.begin();
    while( it_myself != agent_.end() ) {
        if( (*it_myself)->hasNoStandByVirus() ) {                    /* 待機ウイルスが無ければ */
            it_myself++;                                             /* 次のエージェントに */
            continue;                                                /* スキップ */
        } else {                                                     /* あれば */
            infection_count = 0;

            while( ! (*it_myself)->hasNoStandByVirus() ) {           /* 待機ウイルスがなくなるまで */
                if( infection_count >= MAX_V_AGENT_INFECT_ONT_TIME ) { /* もし最大同時感染数を越えそうなら */
                    break;                                           /* 次のエージェントへ */
                }

                n = rand_array( (*it_myself)->getStandByListSize() );   /* ランダムに一個の */
                tv = (*it_myself)->getStandByVirusAt( n );           /* ウイルスを選んで */
                if( (*it_myself)->infection( *tv ) ) {               /* 感染させたら */
                    infection_count++;                               /* カウントを増やす */
                } else {
                    itt = (*it_myself)->getStandByListIteratorBegin();  /* もし感染しなければ */
                    while(n-->0) { itt++; }                          /* そのウイルスを */
                    (*it_myself)->eraseStandByVirus( itt );          /* 待機ウイルスからはずして次のウイルス */
                }
            }
            (*it_myself)->clearStandByVirus();                       /* 待機ウイルスをクリア */
        }
        it_myself++;                                                 /* 次のエージェントに */
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasAllVirus()
 * Description:  すべてのウイルスに感染している数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllVirus() const {
    int ret = 0;
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {                                  /* エージェント全員に対して */
        if( (*it_a)->numHoldingVirus() == NUM_V ) {                  /* 全ウイルスを保持していれば */
            ret++;                                                   /* 数える */
        }
        it_a++;
    }
    return ret;
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: numHasAllImmunity()
 * Description:  すべてのウイルスに対して免疫獲得している数を返す
 *--------------------------------------------------------------------------------------
 */
int Administrator :: numHasAllImmunity() const {
    int ret = 0;
    int flag = 1;
    ITERATOR(Agent *) it_a = agent_.begin();
    while( it_a != agent_.end() ) {
        FOR( j, NUM_V ) {
            if( ! (*it_a)->hasImmunity( virus_[ j ] ) ) {            /* もし免疫を持っていなければ */
                flag = 0;                                            /* フラッグを下ろす */
                break;                                               /* ループを抜ける */
            }
        }
        if( flag == 1 ) ret++;                                       /* 免疫を持って入れば数える */
        flag = 1;                                                    /* フラッグを戻す */
        it_a++;
    }
    return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: initInfectAgentInRatio( Virus &, double )
 * Description:  初期感染させる
 *--------------------------------------------------------------------------------------
 */
void Administrator :: initInfectAgentInRatio( Virus &v, double r ) {
    static int infected_from = 0;                                    /* ０番目のエージェントから順に感染させる */
    int infected_to;
    infected_to = infected_from + (int)( agent_.size() * r );
    REP( i, infected_from, infected_to ) {
        agent_[ i%agent_.size() ]->infection( v );
    }
    infected_from = ( infected_to + 1 ) % agent_.size();             /* 次の感染は、感染した次のエージェントから始まる */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasVirus( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << getTerm() << SEPARATOR;                                   /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << numHasVirus( virus_[j] ) << SEPARATOR;                /* ウイルス j の保持者 */
    }
    int num_has_all = numHasAllVirus();
    ofs << num_has_all << SEPARATOR;                                 /* 全ウイルス保持者 */
    ofs << (double)num_has_all/agent_.size() << SEPARATOR;
    ofs << (double)numHasVirus(virus_[0])/agent_.size() << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_HasImmunity
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_HasImmunity( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << getTerm() << SEPARATOR;                                   /* ファイルに出力 */
    FOR( k, NUM_V ) {
        ofs << numHasImmunity( virus_[k] ) << SEPARATOR;             /* ウイルスに対する免疫獲得者数 */
    }
    int num_has_all = numHasAllImmunity();
    ofs << num_has_all << SEPARATOR;
    ofs << (double)num_has_all/agent_.size() << SEPARATOR;
    ofs << (double)numHasImmunity(virus_[0])/agent_.size() << std::endl;
}
/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_Population
 * Description:  人口推移を出力する
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_Population( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << getTerm() << SEPARATOR;                                   /* 期間 */
    ofs << agent_.size() << SEPARATOR;                               /* 人口 */
    ofs << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void Administrator :: outputFile_InfectionContactRatio( const char *fname ) {
    if( getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    double ratio = 0;
    int sum = 0;                                                     /* 何らかのウイルスに感染した接触回数 */

    ofs << getTerm() << SEPARATOR;                                   /* 期間 */
    ofs << Monitor::Instance().getContactNum() << SEPARATOR;         /* 総接触数 */
    FOR( j, NUM_V ) {                                                /* その内感染した回数 */
        sum += Monitor::Instance().getInfectionContactNum(&virus_[j]);
        ofs << Monitor::Instance().getInfectionContactNum(&virus_[j]) << SEPARATOR;
    }

    if( sum > 0 ) ratio
        = (double)sum / (double) Monitor::Instance().getContactNum(); 
    ofs << ratio << std::endl;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: outputFile_LastLog( const char * )
 * Description:  最終、初期状態を出力
 *--------------------------------------------------------------------------------------
 */
void Administrator :: outputFile_LastLog( const char *fname ) {
    static std::ofstream ofs(fname);
    ofs << "TERM:" << getTerm() << std::endl;
    ofs << "MAX_AGE:" << MAX_AGE << std::endl;
    ofs << "BIRTH_RATE:" << BIRTH_RATE << std::endl;
    ofs << "WIDTH:" << WIDTH << std::endl;
    ofs << "NUM_A:" << agent_.size() << std::endl;
    ofs << "INIT_NUM_A:" << INIT_NUM_A << std::endl;
    ofs << "NUM_V:" << NUM_V << std::endl;
    ofs << "INFECTION_RATE:" << INFECTION_RATE << std::endl;
    ofs << "INIT_INFECTED_RATIO:" << INIT_INFECTED_RATIO << std::endl;
    ofs << "TAG_LEN_A:" << TAG_LEN_A << std::endl;
    ofs << "TAG_LEN_V:" << TAG_LEN_V << std::endl;
    FOR(i,NUM_V) { ofs<<"["<<virus_[i].getLen()<<"]:";
        FOR(j, virus_[i].getLen()) { ofs<<int(virus_[i].tagAt(j)); } ofs<<std::endl; }
    ofs << ">>> Agent Last Status" << std::endl;
    ITERATOR(Agent *) it_a = agent_.begin();
    while(it_a!=agent_.end()) {
        FOR(j, (*it_a)->getLen()) {
            ofs<<(*it_a)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs<<" "<<(*it_a)->numHoldingVirus();                        /* エージェントの保持ウイルス数 */
        ofs<<std::endl;
        it_a++;
    }
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Administrator :: printInitInfo()
 * Description:  初期状態を表示（端末）
 *--------------------------------------------------------------------------------------
 */
void Administrator :: printInitInfo() const {
    std::cout << "WIDTH:" << WIDTH << std::endl;                     /* 幅 */
    std::cout << "\nNUM_A:\t\t" << agent_.size() << std::endl;
    std::cout << "TAG_LEN_A:\t" << TAG_LEN_A << std::endl;
    std::cout << "\nNUM_V:\t\t" << NUM_V << std::endl;

    std::cout << "VIRUS:" << std::endl;                              /* ウイルス情報 */
    FOR(i,NUM_V) { std::cout<<"\trate_"<<i<<":\t"<<virus_[i].getRate();
        std::cout<<"\tlen_"<<i<<":\t"<<virus_[i].getLen()<<std::endl; }
    FOR( i, NUM_V ) virus_[ i ].printTag();                          /* 全ウイルスのタグを表示 */
}
