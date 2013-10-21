#include "Agent.h"
#include "Function.h"

Agent :: Agent( int len ) :
    __TagInterface( len )
{
    log("init agent");
    FOR( i, len_ )
    {
        tag_[ i ] = rand_binary();
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  flip_once
 *  Description:  
 * =====================================================================================
 */
int flip_once( tag_t *a, tag_t *b, int len )    /* 一回だけフリップ */
{
    log(__FUNCTION__);
    FOR( i, len )                               /* タグの長さだけ繰り返す */
    {
        if( *(a+i) == *(b+i) )
        {
            continue;                /* 同じなら次に移動 */
        }
        else                                    /* 違ったら */
        {
            *(a+i) = *(b+i);                            /* ひとつタグをフリップ */
            return 0;                           /* 終了 */
        }
    }
    return -1;                                  /* 同じタグだった */
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
    flip_once( tag_+sp, v.tag_, v.len_ );
}
