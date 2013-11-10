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

#include <vector>

#define LIST_ITERATOR std::vector<VirusData *>::iterator

/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: *
 * Description:  セッタ、ゲッタ関連
 *----------------------------------------------------------------------------------- */
/*
 * エージェントの位置
 */
void Agent :: setX( int x ) { x_ = x; }
void Agent :: setY( int y ) { y_ = y; }
int Agent :: getX() { return x_; }
int Agent :: getY() { return y_; }
/*
 * 保持ウイルスセット
 */
VirusData *Agent :: getVirusDataAt( int n ) { return vlist_.at( n ); }
void Agent :: pushVirusData( VirusData *vd ) { vlist_.push_back( vd ); }
void Agent :: eraseVirusData( std::vector<VirusData *>::iterator it ) { vlist_.erase( it ); }
int Agent :: getVirusListSize() { return vlist_.size(); }
std::vector<VirusData *>::iterator Agent :: getVirusListBeginIterator() { return vlist_.begin(); }
std::vector<VirusData *>::iterator Agent :: getVirusListEndIterator() { return vlist_.end(); }
bool Agent :: hasNoVirusData() { if( vlist_.empty() ) return true; else return false; }
/*
 * 待機ウイルスセット
 */
void Agent :: pushStandByVirus( __TagInterface *v ) { stand_by_list_.push_back( v ); }
bool Agent :: hasNoStandByVirus() { return stand_by_list_.empty(); }
int Agent :: getStandByListSize() { return stand_by_list_.size(); }
__TagInterface *Agent :: getStandByVirusAt( int n ) { return stand_by_list_[n]; }
std::vector<__TagInterface *>::iterator Agent :: getStandByListBeginIterator() { return stand_by_list_.begin(); }
std::vector<__TagInterface *>::iterator Agent :: getStandByListEndIterator() { return stand_by_list_.end(); }
void Agent :: eraseStandByVirus( std::vector<__TagInterface *>::iterator it ) { stand_by_list_.erase( it ); }
void Agent :: clearStandByVirus() { stand_by_list_.clear(); }


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
    stand_by_list_( 0 ),
    monitor_( Monitor::Instance() )
{                                                                              // タグの長さを初期化 
    FOR( i, TAG_LEN_A ) {                                                      // タグをランダムに初期化 
        tag_[ i ] = rand_binary();
    }
    vlist_.clear();                                                            /* 配列を空に */
    stand_by_list_.clear();                                                   /* 配列を空に */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool Agent :: infection( __TagInterface &v )
{
    std::vector<VirusData *>::iterator it = getVirusListBeginIterator();
    while( it != getVirusListEndIterator() ) {                                 // 既に保持しているウイルスなら終了 
        if( (*it)->v_ == &v ) {
            return false;
        }
        it++;
    }
    if( hasImmunity( v ) ) {                                                   // 免疫獲得済みなら 
        return false;                                                          // 感染せずに終了 
    }
    /* 感染リストに追加 */
    VirusData *vdata = new VirusData( v, min_ham_distance( tag_, v.getTag(), len_, v.getLen() ) );     // スタートポイント 
    pushVirusData( vdata );

    monitor_.countUpInfectionContact(vdata->v_);                                /* 感染のために接触した回数を増やす */
    return true;
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

    LIST_ITERATOR it = getVirusListBeginIterator();                            /* 先頭のウイルスに対し */
    flip_once( tag_+(*it)->sp_, (*it)->v_->getTag(), (*it)->v_->getLen() );            /* ひとつフリップ  */

    if( hasImmunity( *((*it)->v_) ) ) {                                        /* 免疫獲得すれば */
        eraseVirusData( it );                                                  /* 保持ウイルスから v を削除 */
    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( __TagInterface & )
 * Description:  免疫を獲得しているかどうか
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( __TagInterface &v )                                 // true -> 免疫獲得済み 
{
    if( min_ham_distance( tag_, v.getTag(), len_, v.getLen() ) < 0 )                   // スタートポイントが -1 以下なら
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
bool Agent :: isInfected( __TagInterface &v ) {
    LIST_ITERATOR it = vlist_.begin();
    while( it != vlist_.end() ) {
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
bool Agent :: hasVirus( __TagInterface &v ) {
    LIST_ITERATOR it = vlist_.begin();
    while( it != vlist_.end() ) {
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
int Agent :: numHoldingVirus() {
    return vlist_.size();
}
