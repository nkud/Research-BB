/*
 * =====================================================================================
 *
 *       Filename:  AgentStrategy.cpp
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Agent.h"
#include "AgentStrategy.h"
#include "Function.h"

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Relocate :: move( int &, int & )
 * Description:  再配置による戦略
 *--------------------------------------------------------------------------------------
 */
void Relocate :: move( int &x, int &y ) {
    x = rand_interval_int( 0, WIDTH-1 );
    y = rand_interval_int( 0, WIDTH-1 );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  RandomWalk :: move( int &, int & )
 * Description:  ランダムウォークによる戦略
 *--------------------------------------------------------------------------------------
 */
void RandomWalk :: move( int &x, int &y ) {
    x += rand_interval_int( -distance_, distance_ );
    y += rand_interval_int( -distance_, distance_ );
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  CoupleTag :: childbirth
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent* CoupleTag :: childbirth( const Agent &a, const Agent &b ) const {
    assert( isOppositeSex( a, b ) );                                 /* 同性ならエラー */

    Agent *child = new Agent(
            a.getMovingStrategy(),
            a.getChildBirthStrategy(),
            a.getLen(),
            b.getLen()
            );                                                       /* 子供を作成 */

    child->resetParam();                                             /* パラメータをリセット */

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
 *--------------------------------------------------------------------------------------
 *      Method:  InheritanceLen :: childbirth
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Agent* InheritanceLen :: childbirth( const Agent &a, const Agent &b ) const {
    assert( isOppositeSex( a, b ) );                                 /* 同性ならエラー */

    Agent *child = new Agent(
            a.getMovingStrategy(),
            a.getChildBirthStrategy(),
            a.getLen(),
            b.getLen()
            );                                                       /* 子供を作成 */

    child->resetParam();                                             /* パラメータをリセット */

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
