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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  VirusList :: search( __TagInterface * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
VirusData *VirusList :: search( __TagInterface *v )
{
    if( head_ == NULL ) {
        crnt_ = NULL;                           // 何もなければNULLをさす 
        return crnt_;                           // 終了 
    }
    VirusData *cursor = head_;
    while( cursor != NULL ) {
        if( cursor->v_ == v ) {
            crnt_ = cursor;                     // 見つかれば今のカーソルをさす 
            return crnt_;
        }
        cursor = cursor->next_;
    }
    crnt_ = NULL;                               // 見つからなければNULLをさす 
    return crnt_;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  VirusList :: insertRear( VirusData * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void VirusList :: insertRear( VirusData *vdata )
{
    if( head_ == NULL ) {
        head_ = vdata;
        return;
    }
    VirusData *cursor = head_;
    while( cursor->next_ != NULL ) {
        cursor = cursor->next_;
    }
    cursor->next_ = vdata;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  VirusList :: removeCurrent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void VirusList :: removeCurrent()
{
    if( head_ == NULL ) {                       // リストに何もないとき 
        return;
    }
    VirusData *cursor = head_;
    if( head_ == cursor ) {                     // リストの一つ目を削除 
        crnt_ = cursor->next_;
        head_ = cursor->next_;
        delete cursor;
        return;
    }
    while( cursor->next_ != crnt_ ) {           // ふたつ以上あるとき 
        log(cursor);
        log(cursor->next_);
        log(crnt_);
        cursor = cursor->next_;
    }
    cursor->next_ = crnt_->next_;
    crnt_ = cursor->next_;
    delete cursor;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  VirusList :: setVirus( VirusData *, __TagInterface *, int, VirusData * )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
VirusData *VirusList :: setVirus( VirusData *vdata, __TagInterface *v, int sp, VirusData *next )
{
    vdata->v_ = v;
    vdata->sp_ = sp;
    vdata->next_ = next;
    return vdata;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: Agent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent :: Agent() :
    __TagInterface( TAG_LEN_A ),                // タグの長さを初期化 
    vlist_(new VirusList)                       // 保持ウイルスリストを作成 
{
    FOR( i, TAG_LEN_A ) {                       // タグをランダムに初期化 
        tag_[ i ] = rand_binary();
    }
    vlist_->head_ = 0;                          // 保持ウイルスリストを初期化 
    vlist_->crnt_ = 0;
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: infection( __TagInterface &v )
{
    VirusData *cursor_vdata = vlist_->head_;

    if( vlist_->search( &v ) ) {                // 既に保持しているウイルスなら終了 
        return;
    }

    if( hasImmunity( v ) ) {                    // 免疫獲得済みなら 
        return;                                 // 感染せずに終了 
    }
    /* 感染リストに追加 */
    VirusData *vdata = vlist_->setVirus(        // 新しいウイルスデータを作成 
            new VirusData,
            &v,
            min_ham_distance( tag_, v.tag_, len_, v.len_ ), // スタートポイント 
            NULL
            );
    vlist_->insertRear( vdata );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: responce( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: response()
{
    if( vlist_->head_ == NULL ) return;         // 保持ウイルスなし、終了 

    VirusData *cursor = vlist_->head_;
    while( cursor != NULL ) {
        flip_once( tag_+cursor->sp_, cursor->v_->tag_, cursor->v_->len_ ); // ひとつフリップ 

        /* 免疫獲得すれば、データを削除する */
        if( hasImmunity( *(cursor->v_) ) ) {
            vlist_->crnt_ = cursor;             // 削除する位置を決定 
            cursor = cursor->next_;             // カーソルを次に移動させておく 
            vlist_->removeCurrent();            // 削除 
        } else {
            cursor = cursor->next_;             // カーソルを次に移動 
        }
    }
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

