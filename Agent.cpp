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
 *      Method:  Agent :: Agent()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent :: Agent() :
    __TagInterface( TAG_LEN_A ),
    vl_(new VirusList)
{
    FOR( i, TAG_LEN_A )                         /* タグをランダムに初期化 */
    {
        tag_[ i ] = rand_binary();
    }
    vl_->head_ = 0;                                /* 保持ウイルスリストを初期化 */
    vl_->crnt_ = 0;
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
VirusData *search( VirusList *vl, __TagInterface *v )
{
    if( vl->head_ == NULL ) {
        vl->crnt_ = NULL;                       /* 何もなければNULLをさす */
        return vl->crnt_;                                 /* 終了 */
    }
    VirusData *cursor = vl->head_;
    while( cursor != NULL ) {
        if( cursor->v_ == v ) {
            vl->crnt_ = cursor;                 /* 見つかれば今のカーソルをさす */
            return vl->crnt_;
        }
        cursor = cursor->next_;
    }
    vl->crnt_ = NULL;                           /* 見つからなければNULLをさす */
    return vl->crnt_;
}
void insert_rear( VirusList *vl, VirusData *vb )
{
    if( vl->head_ == NULL ) {
        vl->head_ = vb;
        return;
    }
    VirusData *cursor = vl->head_;
    while( cursor->next_ != NULL ) {
        cursor = cursor->next_;
    }
    cursor->next_ = vb;
}
void remove_current( VirusList *vl )
{
    if( vl->head_ == NULL ) {                   /* リストに何もないとき */
        return;
    }
    VirusData *cursor = vl->head_;
    if( vl->head_ == cursor ) {               /* リストの一つ目を削除 */
        vl->crnt_ = cursor->next_;
        vl->head_ = cursor->next_;
        delete cursor;
        return;
    }
    while( cursor->next_ != vl->crnt_ ) {       /* ふたつ以上あるとき */
        log(cursor);
        log(cursor->next_);
        log(vl->crnt_);
        cursor = cursor->next_;
    }
    cursor->next_ = vl->crnt_->next_;
    vl->crnt_ = cursor->next_;
    delete cursor;
}
VirusData *set_virus( VirusData *vb, __TagInterface *v, int sp, VirusData *next )
{
    vb->v_ = v;
    vb->sp_ = sp;
    vb->next_ = next;
    return vb;
}

void Agent :: infection( __TagInterface &v )
{
    VirusData *cursor_vb = vl_->head_;

    // hasImmunity
//    while( cursor_vb )                          /*  = > search */
//    {
//        if( cursor_vb->v_ == &v )                /* 既にリストに感染リストに存在なら */
//        {
//            return;                             /* 終了 */
//        }
//        cursor_vb = cursor_vb->next_;            /* 次の感染ウイルス */
//    }
    if( search( vl_, &v ) ) {                  /* 既に保持しているウイルスなら終了 */
        return;
    }

    if( hasImmunity( v ) )                      /* 免疫獲得済みなら */
    {
        return;                                 /* 感染せずに終了 */
    }
    // 感染リストに追加
    VirusData *vb = set_virus(                /* 新しいウイルスデータを作成 */
            new VirusData,
            &v,
            min_ham_distance( tag_, v.tag_, len_, v.len_ ), /* スタートポイント */
            NULL
            );

    // 末尾に挿入
    insert_rear( vl_, vb );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: responce( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: response()
{
    if( vl_->head_ == NULL ) return;            /* 保持ウイルスなし、終了 */

    VirusData *cursor = vl_->head_;
    while( cursor != NULL ) {
        flip_once( tag_+cursor->sp_, cursor->v_->tag_, cursor->v_->len_ ); /* ひとつフリップ */

        // 免疫獲得すれば、データを削除する
        if( hasImmunity( *(cursor->v_) ) ) {
            vl_->crnt_ = cursor;                /* 削除する位置を決定 */
            cursor = cursor->next_;             /* カーソルを次に移動させておく */
            remove_current( vl_ );              /* 削除 */
        } else {
            cursor = cursor->next_;             /* カーソルを次に移動 */
        }
    }
}

/* 
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: hasImmunity( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
bool Agent :: hasImmunity( __TagInterface &v )  /* true -> 免疫獲得済み */
{
    if( min_ham_distance( tag_, v.tag_, len_, v.len_ ) < 0 ) /* 最小が -1 以下なら*/
        return true;                            /* 免疫獲得済み */
    else                                        /* 0 以上なら*/
        return false;                           /* 未獲得 */
}

