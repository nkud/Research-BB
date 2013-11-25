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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: Agent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent :: Agent() :
    __TagInterface( TAG_LEN_A ),
    x_( 0 ),
    y_( 0 ),
    age_( 0 ),
    sex_( __MALE__ ),
    life_( __ALIVE__ ),
    stand_by_list_( 0 )
{
    vlist_ = new std::vector<VirusData *>;      /* 保持ウイルスリストを初期化 */
    stand_by_list_ = new std::vector<Virus *>;  /* 待機ウイルスリストを初期化 */

    if( rand_binary() ) sex_ = __MALE__;        /* 性別をランダムに初期化 */
    else sex_ = __FEMALE__;

    FOR( i, TAG_LEN_A )
    {
        tag_[ i ] = rand_binary();              /* タグをランダムに初期化  */
    }

    (*vlist_).reserve( NUM_V );                 /* 領域確保 */
    (*stand_by_list_).reserve( NUM_V );         /* 領域確保 */
    (*vlist_).clear();                          /* 配列を空に */
    (*stand_by_list_).clear();                  /* 配列を空に */
}

Agent :: ~Agent() {
    static int i = 0;
    i++;
    log("die");
    log(i);
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: resetParam()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: resetParam() {
    age_ = 0;
    sex_ = __MALE__;
    life_ = __ALIVE__;
    (*vlist_).clear();
    (*stand_by_list_).clear();
}
/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
/*
 * エージェントの位置
 */
void Agent :: setX( int x ) { x_ = x; }
void Agent :: setY( int y ) { y_ = y; }
int Agent :: getX() const { return x_; }
int Agent :: getY() const { return y_; }
/*
 * 保持ウイルスセット
 */
VirusData *Agent :: getVirusDataAt( int n ) const { return (*vlist_).at( n ); }
void Agent :: pushVirusData( VirusData *vd ) { (*vlist_).push_back( vd ); }
void Agent :: eraseVirusData( std::vector<VirusData *>::iterator it ) { (*vlist_).erase( it ); }
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
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Agent :: aging() {
    age_++;
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
    if( getVirusListSize() >= MAX_VIRUS_AGENT_HAVE ) {      /* 最大値を越えてたら */
        return false;                                      /* 感染せずに終了 */
    }
    ITERATOR(VirusData *) it = getVirusListIteratorBegin();
    while( it != getVirusListIteratorEnd() ) {             /* 既に保持しているウイルスなら終了 */
        if( (*it)->v_ == &v ) {
            return false;
        }
        it++;
    }
    if( hasImmunity( v ) ) {                               /* 免疫獲得済みなら  */
        return false;                                      /* 感染せずに終了 */
    }
    /* 感染リストに追加  */
    VirusData *vdata = new VirusData( v, min_ham_distance_point( tag_, v.getTag(), len_, v.getLen() ) );     /* スタートポイント */
    pushVirusData( vdata );

    Monitor::Instance().countUpInfectionContact(vdata->v_);                                /* 感染のために接触した回数を増やす */
    return true;                                           /* 感染したら true を返す */
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
    if( hasNoVirusData() ) return;                                             /* 保持ウイルスなし、終了  */

    ITERATOR(VirusData *) it = getVirusListIteratorBegin();                            /* 先頭のウイルスに対し */
    flip_once( tag_+(*it)->sp_, (*it)->v_->getTag(), (*it)->v_->getLen() );            /* ひとつフリップ  */

    if( hasImmunity( *((*it)->v_) ) ) {                                        /* 免疫獲得すれば */
        eraseVirusData( it );                                                  /* 保持ウイルスから v(先頭) を削除 */
    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( __TagInterface & )
 * Description:  免疫を獲得しているかどうか
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( __TagInterface &v ) const                                 // true -> 免疫獲得済み 
{
    if( min_ham_distance_point( tag_, v.getTag(), len_, v.getLen() ) < 0 )                   // スタートポイントが -1 以下なら
        return true;                                                           // 免疫獲得済み 
    else                                                                       // 0 以上なら
        return false;                                                          // 未獲得 
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: isInfected( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
bool Agent :: isInfected( __TagInterface &v ) const {
    C_ITERATOR(VirusData *) it = (*vlist_).begin();
    while( it != (*vlist_).end() ) {
        if( (*it)->v_ == &v ) {                                                // 感染済みだった
            return true;
        }
        it++;
    }
    return false;                                                              // 未感染だった
}

/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasVirus( __TagInterface & )
 * Description:  特定のウイルスを保持しているかどうか
 *               リストを走査することで確かめる
 *----------------------------------------------------------------------------------- */
bool Agent :: hasVirus( __TagInterface &v ) const {
    C_ITERATOR(VirusData *) it = (*vlist_).begin();
    while( it != (*vlist_).end() ) {
        if( (*it)->v_ == &v ) {                                                // 感染済みだった
            return true;
        }
        it++;
    }
    return false;                                                              // 未感染だった
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: numHoldingVirus()
 * Description:  保持しているウイルスの数
 *--------------------------------------------------------------------------------------
 */
int Agent :: numHoldingVirus() const {
    return getVirusListSize();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  die( Agent & )
 *  Description:  
 * =====================================================================================
 */
void die( Agent &a ) {
    a.setLife( __DEATH__ );                     /* 死亡する */
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  childbirth( Agent &, Agent & )
 *  Description:  親から子を作成する。
 *                タグはそれぞれからもらう。
 * =====================================================================================
 */
void childbirth( Agent &child, const Agent &a, const Agent &b ) {
    if( ! isOppositeSex( a, b ) ) return;       /* 同性なら終了 */

    child.resetParam();
    child.changeTagLenTo( TAG_LEN_A );

    tag_t *couple_tag = new tag_t[ a.getLen() + b.getLen() ];
    tag_t *p = couple_tag;

    FOR( i, a.getLen() ) {
        *(p++) = a.tagAt( i );
    }
    FOR( i, b.getLen() ) {
        *(p++) = b.tagAt( i );
    }
    child.setTag( couple_tag+rand_interval_int(0,a.getLen()) , TAG_LEN_A );
    if( a.getSex() == __FEMALE__ ) {
        int tx = a.getX();
        int ty = a.getY();
        child.setX( tx );
        child.setY( ty );
    } else {
        int tx = b.getX();
        int ty = b.getY();
        child.setX( tx );
        child.setY( ty );
    }

    delete[] couple_tag;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isOppositeSex( Agent &, Agent & )
 *  Description:  異性であれば true
 * =====================================================================================
 */
bool isOppositeSex( const Agent &a, const Agent &b ) {
    if( a.getAge() == b.getAge() ) {            /* 性別が同じなら */
        return false;                           /* false */
    } else {                                    /* 異なれば */
        return true;                            /* true */
    }
}
