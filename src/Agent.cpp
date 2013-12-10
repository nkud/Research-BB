/*
 * =====================================================================================
 *
 *       Filename:  Agent.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */
#include "Agent.h"
#include "Function.h"
#include "Monitor.h"
#include "Global.h"
#include "TagInterface.h"

#include <vector>
#include <cassert>
#include <cstring>
#include <iostream>

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: Agent() / ~Agent()
 * Description:  コンストラクタ、デストラクタ
 *               性別はランダムに初期化
 *               寿命は０才から最大年齢までの範囲でランダムに初期化
 *--------------------------------------------------------------------------------------
 */
Agent :: Agent() :
    __TagInterface( TAG_LEN_A ),
    x_( 0 ),
    y_( 0 ),
    age_( 0 ),
    sex_( __MALE__ ),
    life_( __ALIVE__ ),
    stand_by_list_( 0 ),
    count_get_new_immunity_( 0 )
{
    vlist_ = new std::vector<VirusData *>;                           /* 保持ウイルスリストを初期化 */
    stand_by_list_ = new std::vector<Virus *>;                       /* 待機ウイルスリストを初期化 */

    if( rand_binary() == 0 ) { sex_ = __MALE__;                      /* 性別をランダムに初期化 */
    } else { sex_ = __FEMALE__; }

    FOR( i, TAG_LEN_A )
    {
        tag_[i] = rand_binary();                                     /* タグをランダムに初期化  */
    }

    age_ = rand_interval_int( 0, MAX_AGE );                          /* 寿命をランダムに設定 */

    (*vlist_).reserve( NUM_V );                                      /* 領域確保 */
    (*stand_by_list_).reserve( NUM_V );                              /* 領域確保 */
}

/* デストラクタ */
Agent :: ~Agent() {
    delete vlist_;
    delete stand_by_list_;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: resetParam()
 * Description:  エージェントのパラメータをリセット
 *               年齢は０才で初期化
 *--------------------------------------------------------------------------------------
 */
void Agent :: resetParam() {
    age_ = 0;                                                        /* ０才で初期化 */
    if( rand_binary() == 0 ) { sex_ = __MALE__;                      /* 性別をランダムに初期化 */
    } else { sex_ = __FEMALE__; }
    life_ = __ALIVE__;                                               /* 生存 */
    (*vlist_).clear();                                               /* 保持ウイルスリストクリア */
    (*stand_by_list_).clear();                                       /* 待機ウイルスリストクリア */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: birthChild *
 * Description:  出産関連の関数
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasAlreadyGiveBirth() {
    if( give_birth_ ) {                                              /* 出産済みなら */
        return true;                                                 /* true */
    } else {                                                         /* そうでないなら */
        return false;                                                /* false */
    }
}
void Agent :: setGiveBirth() {
    give_birth_ = true;                                              /* 出産後にする */
}
void Agent :: resetGiveBirth() {
    give_birth_ = false;                                             /* 未出産にする */
}
/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
/*
 * エージェントの位置
 */
void Agent :: setX( int x ) { x_ = x; }                              /* エージェントの位置を設定 */
void Agent :: setY( int y ) { y_ = y; }                              /* エージェントの位置を設定 */
int Agent :: getX() const { return x_; }                             /* エージェントの位置を返す */
int Agent :: getY() const { return y_; }                             /* エージェントの位置を返す */
/*
 * 保持ウイルスセット
 */
VirusData *Agent :: getVirusDataAt( int n ) const { return (*vlist_).at( n ); }
void Agent :: pushVirusData( VirusData *vd ) { (*vlist_).push_back( vd ); }
void Agent :: eraseVirusData( std::vector<VirusData *>::iterator it ) { delete (*it); (*vlist_).erase( it ); }
int Agent :: getVirusListSize() const { return (*vlist_).size(); }
std::vector<VirusData *>::iterator Agent :: getVirusListIteratorBegin() { return (*vlist_).begin(); }
std::vector<VirusData *>::iterator Agent :: getVirusListIteratorEnd() { return (*vlist_).end(); }
bool Agent :: hasNoVirusData() const { if( (*vlist_).empty() ) return true; else return false; }
/*
 * 待機ウイルスセット
 */
void Agent :: pushStandByVirus( Virus *v ) { (*stand_by_list_).push_back( v ); }
bool Agent :: hasNoStandByVirus() const { return (*stand_by_list_).empty(); }
int Agent :: getStandByListSize() const { return (*stand_by_list_).size(); }
Virus *Agent :: getStandByVirusAt( int n ) const { return (*stand_by_list_).at(n); }
std::vector<Virus *>::iterator Agent :: getStandByListIteratorBegin() { return (*stand_by_list_).begin(); }
std::vector<Virus *>::iterator Agent :: getStandByListIteratorEnd() { return (*stand_by_list_).end(); }
void Agent :: eraseStandByVirus( std::vector<Virus *>::iterator it ) { (*stand_by_list_).erase( it ); }
void Agent :: clearStandByVirus() { (*stand_by_list_).clear(); }
/* パラメータ */
__LABEL__ Agent :: getSex() const { return sex_; }
int Agent :: getAge() const { return age_; }

void Agent :: setLife( __LABEL__ l ) { life_ = l; }
bool Agent :: isAlive() const { if( life_ == __ALIVE__ ) return true; else return false; }
bool Agent :: isDead() const { if( life_ == __DEATH__ ) return false; else return true; }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: aging
 * Description:  老化する
 *--------------------------------------------------------------------------------------
 */
int Agent :: aging() {
    age_++;                                                          /* 年齢をインクリメント */
    return age_;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool Agent :: infection( Virus &v )
{
    if( getVirusListSize() >= MAX_VIRUS_AGENT_HAVE ) {               /* 最大値を越えてたら */
        return false;                                                /* 感染せずに終了 */
    }
    ITERATOR(VirusData *) it_vd = getVirusListIteratorBegin();       /* 保持ウイルスリストを取得 */
    while( it_vd != getVirusListIteratorEnd() ) {                    /* 既に保持しているウイルスなら */
        if( (*it_vd)->v_ == &v ) {
            return false;                                            /* 感染せずに終了 */
        }
        it_vd++;                                                     /* 次の保持ウイルス */
    }
    if( hasImmunity( v ) ) {                                         /* 免疫獲得済みなら  */
        return false;                                                /* 感染せずに終了 */
    }
    VirusData *vdata                                                 /* 新しいウイルスデータを作成して */
//        = new VirusData( v, min_ham_distance_point( tag_, v.getTag(), len_, v.getLen() ) );
        = new VirusData( v, v.searchStartPoint( *this ) );
    pushVirusData( vdata );                                          /* 保持ウイルスリストに追加する */

    Monitor::Instance().countUpInfectionContact(vdata->v_);          /* 感染のために接触した回数を増やす */
    return true;                                                     /* 感染して true を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: responce( __TagInterface & )
 * Description:  先頭のウイルスに対する免疫を獲得するまで、
 *               １期間に１つタグをフリップさせていく。
 *--------------------------------------------------------------------------------------
 */
void Agent :: response()
{
    if( hasNoVirusData() ) return;                                   /* 保持ウイルスなし、終了する */

    ITERATOR(VirusData *) it = getVirusListIteratorBegin();          /* 先頭のウイルスに対し */
    flip_once( tag_+(*it)->sp_, (*it)->v_->getTag(), (*it)->v_->getLen() );            /* ひとつフリップする */

    if( hasImmunity( *((*it)->v_) ) )
    {                                                                /* 免疫獲得すれば */
        // XXX: 要検討
        count_get_new_immunity_virus_[ (*it)->v_ ]++;                /* そのウイルスの免疫獲得した回数を１増やす */
        count_get_new_immunity_++;                                   /* 免疫獲得した回数を１増やす */

        eraseVirusData( it );                                        /* 保持ウイルスから v(先頭) を削除して */
    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( Virus & )
 * Description:  免疫を獲得しているかどうか
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( const Virus &v ) const                 /* true -> 免疫獲得済み  */
{
    if( min_ham_distance_point( tag_, v.getTag(), len_, v.getLen() ) < 0 )                   /* スタートポイントが -1 以下なら */
        return true;                                                 /* 免疫獲得済み */
    else                                                             /* 0 以上なら */
        return false;                                                /* 未獲得 */
}

/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasVirus( __TagInterface & )
 * Description:  特定のウイルスを保持しているかどうか
 *               リストを走査することで確かめる
 *----------------------------------------------------------------------------------- */
bool Agent :: hasVirus( __TagInterface &v ) const {
    C_ITERATOR(VirusData *) it_vd = (*vlist_).begin();               /* ウイルスリストの先頭から */
    while( it_vd != (*vlist_).end() ) {                              /* 末尾まで */
        if( (*it_vd)->v_ == &v ) {                                   /* 感染済みであれば */
            return true;                                             /* true を返す */
        }
        it_vd++;
    }
    return false;                                                    /* 未感染なので false を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: numHoldingVirus()
 * Description:  保持しているウイルスの数
 *--------------------------------------------------------------------------------------
 */
int Agent :: numHoldingVirus() const {
    return getVirusListSize();                                       /* ウイルスリストのサイズを返す */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  die( Agent & )
 *  Description:  
 * =====================================================================================
 */
void die( Agent &a ) {
    a.setLife( __DEATH__ );                                          /* 死亡する */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  childbirth( Agent &, Agent & )
 *  Description:  親から子を作成する。
 *                タグはそれぞれからもらう。
 * =====================================================================================
 */
Agent* childbirth( const Agent &a, const Agent &b ) {
    assert( isOppositeSex( a, b ) );                                 /* 同性ならエラー */

    Agent *child = new Agent;                                        /* 子供を作成 */

    child->resetParam();                                             /* パラメータをリセット */

#ifdef COUPLE_TAG
    child->changeTagLenTo( TAG_LEN_A );                              /* タグの長さを設定 */

    tag_t *couple_tag = new tag_t[ a.getLen() + b.getLen() ];        /* 両親を元にした */
    tag_t *p = couple_tag;                                           /* カップルタグを作成 */

    FOR( i, a.getLen() ) {                                           /* 両親の */
        *(p++) = a.tagAt( i );                                       /* タグを */
    }
    FOR( i, b.getLen() ) {                                           /* コピーしていく */
        *(p++) = b.tagAt( i );
    }
    child->setTag(                                                   /* カップルタグを元に */
            couple_tag+rand_interval_int(0,a.getLen()) , TAG_LEN_A   /* 子供のタグを作成 */
            );
    delete[] couple_tag;                                             /* カップルタグを削除 */
#endif

    if( a.getSex() == __FEMALE__ ) {                                 /* 母親の居場所に */
        int tx = a.getX();
        int ty = a.getY();
        child->setX( tx );                                           /* 子供を配置 */
        child->setY( ty );
    } else {
        int tx = b.getX();
        int ty = b.getY();
        child->setX( tx );
        child->setY( ty );
    }

    return child;                                                    /* 子供を返す */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isOppositeSex( Agent &, Agent & )
 *  Description:  異性であれば true
 * =====================================================================================
 */
bool isOppositeSex( const Agent &a, const Agent &b ) {
    if( a.getSex() == b.getSex() ) {                                 /* 性別が同じなら */
        return false;                                                /* false */
    } else {                                                         /* 異なれば */
        return true;                                                 /* true */
    }
}
