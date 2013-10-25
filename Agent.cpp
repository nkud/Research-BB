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

#include <list>

#define LIST_ITERATOR std::list<VirusData>::iterator

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: Agent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent :: Agent() :
    __TagInterface( TAG_LEN_A ) {               // タグの長さを初期化 
    FOR( i, TAG_LEN_A ) {                       // タグをランダムに初期化 
        tag_[ i ] = rand_binary();
    }
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: infection( __TagInterface &v )
{
    std::list<VirusData>::iterator it = vlist_.begin();
    while( it != vlist_.end() ) {             // 既に保持しているウイルスなら終了 
        if( it->v_ == &v ) {
            return;
        }
        it++;
    }
    if( hasImmunity( v ) ) {                    // 免疫獲得済みなら 
        return;                                 // 感染せずに終了 
    }
    /* 感染リストに追加 */
    VirusData vdata( &v, min_ham_distance( tag_, v.tag_, len_, v.len_ ) ); // スタートポイント 
    vlist_.push_back( vdata );
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

    LIST_ITERATOR it = vlist_.begin();
    //    while( it != vlist_.end() ) {
    flip_once( tag_+it->sp_, it->v_->tag_, it->v_->len_ ); /* ひとつフリップ  */

    if( hasImmunity( *(it->v_) ) ) {            /* 免疫獲得すれば */
        std::list<VirusData>::iterator ep = it;
//        it++;
        vlist_.erase( ep );                     /* リストから v を削除 */
//        continue;
    }
//        it++;
//    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( __TagInterface &v )  // true -> 免疫獲得済み 
{
    if( min_ham_distance( tag_, v.tag_, len_, v.len_ ) < 0 ) // 最小が -1 以下なら
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
        if( it->v_ == &v ) { // 感染済みだった
            return true;
        }
        it++;
    }
    return false; // 未感染だった
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: numHoldingVirus()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Agent :: numHoldingVirus() {
    return vlist_.size();
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  AgentManager :: numIsInfected( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int AgentManager :: numIsInfected( __TagInterface &v ) {
    int ret = 0;

    FOR( i, num_agent_ ) {
        if( agent_[i].isInfected( v ) ) {       /* v に感染していれば */
            ret++;                              /* インクリメント */
        }
    }
    return ret;                                 /* v の感染者数を返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  AgentManager :: numHasImmunity( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int AgentManager :: numHasImmunity( __TagInterface &v ) {
    int ret = 0;

    FOR( i, num_agent_ ) {
        if (agent_[i].hasImmunity( v ) ) {
            ret++;
        }
    }
    return ret;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  AgentManager :: allResponse()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void AgentManager :: allResponse() {
    FOR( i, num_agent_ ) {
        agent_[ i ].response();
    }
}
