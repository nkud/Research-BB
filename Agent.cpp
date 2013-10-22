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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_once
 *  Description:  
 * =====================================================================================
 */
int flip_once( tag_t *a, tag_t *b, int len )    /* 一回だけフリップ */
{
    FOR( i, len )                               /* タグの長さだけ繰り返す */
    {
        if( *(a+i) == *(b+i) )
        {
            continue;                           /* 同じなら次に移動 */
        }
        else                                    /* 違ったら */
        {
            *(a+i) = *(b+i);                    /* ひとつタグをフリップ */
            return 0;                           /* 終了 */
        }
    }
    return -1;                                  /* 同じタグだった */
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: infection( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void insert_rear( VirusList *vl, VirusBuffer *vb )
{
    if( vl->head_ == NULL ) {
        vl->head_ = vb;
    }
    else {
        VirusBuffer *cursor = vl->head_;
        while( cursor->next_ != NULL ) {
            cursor = cursor->next_;
        }
        cursor->next_ = vb;
    }
}
void remove_current( VirusList *vl, VirusBuffer *vb )
{
    if( vl->head_ == NULL ) {
        return;
    }
    VirusBuffer *cursor = vl->head_;
    while( cursor->next_ != vl->crnt_ ) {
        cursor = cursor->next_;
    }
    cursor->next_ = vl->crnt_->next_;
    delete vl->crnt_;
}

void Agent :: infection( __TagInterface &v )
{
    VirusBuffer *cursor_vb = vl_->head_;

    // hasImmunity
    while( cursor_vb )                          /*  = > search */
    {
        if( cursor_vb->v_ == &v )                /* 既にリストに感染リストに存在なら */
        {
            return;                             /* 終了 */
        }
        cursor_vb = cursor_vb->next_;            /* 次の感染ウイルス */
    }
    if( hasImmunity( v ) )                      /* 免疫獲得済みなら */
    {
        return;                                 /* 感染せずに終了 */
    }
    // 感染リストに追加
    VirusBuffer *vb = new VirusBuffer;

    // set vb
    vb->sp_ = min_ham_distance( tag_, v.tag_, len_, v.len_ );
    vb->v_ = &v;
    vb->next_ = 0;

    // 末尾に挿入
    insert_rear( vl_, vb );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Agent :: responce( __TagInterface & )
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Agent :: response( __TagInterface &v )
{
    int sp = min_ham_distance( tag_, v.tag_, len_, v.len_ );
    if( flip_once( tag_+sp, v.tag_, v.len_ )  == -1 )
    {

    }
}

