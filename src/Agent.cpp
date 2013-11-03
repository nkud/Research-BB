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

#define LIST_ITERATOR std::vector<VirusData>::iterator

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
    stand_by_virus_( 0 ),
    monitor_( Monitor::Instance() )
{                                               // タグの長さを初期化 
    FOR( i, TAG_LEN_A ) {                       // タグをランダムに初期化 
        tag_[ i ] = rand_binary();
    }
    vlist_.clear();                             /* 配列を空に */
    stand_by_virus_.clear();                    /* 配列を空に */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  感染したら、true を返す
 *--------------------------------------------------------------------------------------
 */
bool Agent :: infection( __TagInterface &v )
{
    std::vector<VirusData>::iterator it = vlist_.begin();
    while( it != vlist_.end() ) {               // 既に保持しているウイルスなら終了 
        if( it->v_ == &v ) {
            return false;
        }
        it++;
    }
    if( hasImmunity( v ) ) {                    // 免疫獲得済みなら 
        return false;                                 // 感染せずに終了 
    }
    /* 感染リストに追加 */
    VirusData vdata( &v, min_ham_distance( tag_, v.tag_, len_, v.len_ ) ); // スタートポイント 
    vlist_.push_back( vdata );

    monitor_.countUpInfectionContact(vdata.v_);       /* 感染のために接触した回数を増やす */
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
    if( vlist_.empty() ) return;                /* 保持ウイルスなし、終了  */

    LIST_ITERATOR it = vlist_.begin();          /* 先頭のウイルスに対し */
    flip_once( tag_+it->sp_, it->v_->tag_, it->v_->len_ ); /* ひとつフリップ  */

    if( hasImmunity( *(it->v_) ) ) {            /* 免疫獲得すれば */
        vlist_.erase( it );                     /* 保持ウイルスから v を削除 */
    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( __TagInterface & )
 * Description:  免疫を獲得しているかどうか
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( __TagInterface &v )  // true -> 免疫獲得済み 
{
    if( min_ham_distance( tag_, v.tag_, len_, v.len_ ) < 0 ) // スタートポイントが -1 以下なら
        return true;                            // 免疫獲得済み 
    else                                        // 0 以上なら
        return false;                           // 未獲得 
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
        if( it->v_ == &v ) {                    // 感染済みだった
            return true;
        }
        it++;
    }
    return false;                               // 未感染だった
}

/*--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasVirus( __TagInterface & )
 * Description:  特定のウイルスを保持しているかどうか
 *               リストを走査することで確かめる
 *----------------------------------------------------------------------------------- */
bool Agent :: hasVirus( __TagInterface &v ) {
    LIST_ITERATOR it = vlist_.begin();
    while( it != vlist_.end() ) {
        if( it->v_ == &v ) {                    // 感染済みだった
            return true;
        }
        it++;
    }
    return false;                               // 未感染だった
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