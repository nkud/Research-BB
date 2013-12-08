/*
 * =====================================================================================
 *
 *       Filename:  Virus.h
 *
 *    Description:  ウイルスのクラス
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___VIRUS
#define ___VIRUS

#include "TagInterface.h"

class __SearchPattern;

enum __SEARCH__TYPE__{
    __NORMAL__,
    __FIXED__
};

/*
 * =====================================================================================
 *        Class:  Virus
 *  Description:  ウイルス
 * =====================================================================================
 */
class Virus : public __TagInterface                                  /* ウイルスのクラス*/
{
        double rate_;                                                /* 感染確率 */
        __SearchPattern *search_pattern_;

    public:
        Virus( const char * );                                       /* コンストラクタ: タグ */
        Virus( int, double );                                        /* コンストラクタ: タグ長, 感染率 */
        Virus();                                                     /* コンストラクタ: default */

        /* 戦略指定コンストラクタ */
        Virus( __SearchPattern * );                                  /* コンストラクタ: 戦略 */
        Virus( int, __SearchPattern * );                             /* コンストラクタ: タグ長, 戦略 */

        double getRate() const;                                      /* 感染確率を返す */
        void setRate( const double r );                              /* 感染確率を設定 */

        int searchStartPoint( const __TagInterface & ) const;        /* タグに取り付く位置を返す */
        __SEARCH__TYPE__ getSearchType() const;
};

/* =====================================================================================
 *        Class:  __SearchPattern
 *  Description:  タグに取り付く戦略のクラス
 *                ストラテジーパターン
 * ================================================================================== */
class __SearchPattern {
    public:
        virtual int searchStartPoint( const __TagInterface &, const __TagInterface & ) const = 0;
        virtual __SEARCH__TYPE__ getSearchType() const = 0;
};

class Fixed : public __SearchPattern {
    private:
        int sp_;
    public:
        Fixed( int n ) : sp_( n ) { }
        virtual int searchStartPoint( const __TagInterface &, const __TagInterface & ) const;
        virtual __SEARCH__TYPE__ getSearchType() const;
};

class Normal : public __SearchPattern {
    public:
        virtual int searchStartPoint( const __TagInterface &myself, const __TagInterface &tag ) const;
        virtual __SEARCH__TYPE__ getSearchType() const;
};

#endif
