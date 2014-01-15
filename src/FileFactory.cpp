/*
 * =====================================================================================
 *
 *       Filename:  FileFactory.cpp
 *
 *    Description:  
 *
 *         Author: Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include <fstream>
#include <string>
#include <cstring>

#include "FileFactory.h"
#include "Administrator.h"
#include "Agent.h"
#include "Virus.h"
#include "Global.h"
#include "Monitor.h"
#include "Benchmark.h"

#define AUTO_GPLOT_FILENAME     "auto.plt"
#define FNAME_RESULT_HTML       "RESULT.html"

/*-----------------------------------------------------------------------------
 *  マクロ
 *-----------------------------------------------------------------------------*/
#define OFS(str)                        do { ofs<< str; }while(0);
#define OFSS(str)                       ofs << #str << std::endl;

#define OFSV(str)                       do { ofs << #str << " " << str << std::endl; }while(0);
#define OFSD(str)                       do { ofs << #str << " " << str << std::endl; }while(0);
#define OFSVP(str,val)                  do { ofs << #str << " " << val << std::endl; }while(0);

#define OFS_P(str)                      do { ofs<<"<p>"<<str<<"</p>"<<std::endl; }while(0);
#define OFS_LINE(str)                   do { ofs<< str << std::endl; }while(0);
#define OFS_IMG_MINI(img,mini,last)     do { ofs<<"<table class=\"graph\"><tr> \
    <td><img src=assets/"<<img<<" /></td></tr><tr> \
    <td><img src=assets/"<<mini<<" /></td></tr><t> \
    <td><img src=assets/"<<last<<" /></td></tr> \
    </table><br />"<<std::endl; }while(0);

#define OFS_TD(str,val)                 do { ofs<<"<tr><td>"<<str<<"</td>"<<"<td>"<<val<<"</td></tr>"<<std::endl; }while(0);

#define QUO(str)                        "\"" << str << "\""

#define OFS_TITLE(t, x, y)              OFSS( set title #t ) OFSS( set xl #x ) OFSS( set yl #y ) OFSS( set key box below left )

#define OFS_PLOT_PERIOD(png, b, e)             ofs << "set output " << #png << ";plot [" << b << ":" << e << "] "
#define OFS_PLOT(png)                   ofs << "set output " << #png << ";plot "
#define OFS_REPLOT(png)                 ofs << "set output " << #png << ";replot "

#define ENDL                            std::endl

/*-----------------------------------------------------------------------------
 *  スタイル
 *-----------------------------------------------------------------------------*/
#define LINE_STYLE                      " with l lw 2 "
// #define LINE_STYLE_2                    " with i lt 0 lw 2 "
#define LINE_STYLE_2                    " with p ps 2 pt 4 "
#define FONT_STYLE                      " font \"helvetica, 20\" "
#define TITLE(str)                      " title \"" << #str << "\" "
#define TITLE_N(str, n)                 " title \"" << #str << n << "\" "
#define USING(x,y)                      " using " << x << ":" << y << " "

#define PLOT_STYLE                      OFSS( set style line 1 lw 2 );

/*-----------------------------------------------------------------------------
 *  出力ファイル名
 *-----------------------------------------------------------------------------*/
#define HAS_VIRUS_OUTPUT                QUO( HAS_VIRUS_FNAME )
#define HAS_IMMUNITY_OUTPUT             QUO( HAS_IMMUNITY_FNAME )
#define CONTACT_OUTPUT                  QUO( CONTACT_FNAME )
#define POPULATION_OUTPUT               QUO( POPULATION_FNAME )
#define AVE_GOT_NEW_IMMUNITY_OUTPUT     QUO( AVE_GOT_NEW_IMMUNITY_FNAME )

#define PEAK_PREFIX                     "PEAK_"

#define PERIOD                          100                          /* 調査する区間 */
#define CHECK_INTERVAL                  4

int averate_amplitude_;                                              /* 平均振幅 */


/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: Instance()
 * Description:  インスタンスを返す
 *--------------------------------------------------------------------------------------
 */

FileFactory& FileFactory :: Instance() {
    static FileFactory coredata;
    return coredata;                                                 /* インスタンスを返す */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: setadmi
 * Description:  管理者を登録する
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: setAdministrator( Administrator &admin ) {
    admin_ = &admin;                                                 /* 管理者を登録 */
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_peakSearch()
 * Description:  ピークサーチする
 *--------------------------------------------------------------------------------------
 */
int max_term_in_interval( const int data[], int cursor, int len ) {
    /*-----------------------------------------------------------------------------
     *  与えられた期間の最大値を検索する
     *-----------------------------------------------------------------------------*/
    int mv = 0;
    int mt = 0;
    FOR( i, len ) {                                                  /* 検索範囲だけ */
        if( cursor+i >= TERM ) continue;                             /* 添字が０未満ならスキップ */
        if( data[cursor+i] > mv ) {                                  /* 現最大値より大きければ */
            mv = data[cursor+i];                                     /* 最大値を更新し */
            mt = i;                                                  /* 期間を記録する */
        }
    }
    return cursor + mt;
}

double average_cycle( const char *origin_fname ) {
    /*-----------------------------------------------------------------------------
     *  そのファイルの平均周期を求める
     *-----------------------------------------------------------------------------*/
    std::ifstream ifs( origin_fname, std::ios::in );
    std::string line;
    int t, v;
    int n = 0;
    int pre = 0;
    int sum = 0;

    while( std::getline( ifs, line ) )
    {
        std::sscanf( line.data(), "%d %d", &t, &v );
        n++;
        if( pre == 0 ) {
            pre = t;
        } else {
            sum += t - pre;
            pre = t;
        }
    }
    return (double)sum/n;
}
//
// XXX: need check
double FileFactory :: outputFile_peakSearch( const char *origin_fname ) const {
    std::string line;
    std::ifstream ifs( origin_fname, std::ios::in );                 /* ウイルス保持者出力を読込専用で開く */
    char prefix[256] = PEAK_PREFIX;
    char *fname = strcat(prefix, origin_fname);                      /* 元のファイル名に接頭辞を付ける */
    std::ofstream ofs( fname );                                      /* 出力先ファイル */

    int t, v;
    int term = 0;
    int data[TERM];
    int vmax = 0;
    int vmin = INIT_NUM_A;
    while( std::getline( ifs, line ) ) {                             /* １行ずつ読み取って */
        std::sscanf( line.data(), "%d %d", &t, &v );                 /* 期間を読み込む */
        data[ term++ ] = v;
        if( t > TERM-MINI_SIZE_TERM ) {                              /* 最後の期間の */
            if( vmax < v ) vmax = v;                                 /* 最大値 */
            if( vmin > v ) vmin = v;                                 /* 最小値 */
        }
    }
    averate_amplitude_ = vmax - vmin;                                /* 平均振幅＝最大値−最小値 */

    int mt = 0;                                                      /* その期間での最大時刻 */
    int count = 1;                                                   /* カウンタ */
    int temp;
    FOR( i, TERM ) {
        temp = max_term_in_interval( data, i, CHECK_INTERVAL );      /* その期間での最大時刻と */
        if( data[temp] == data[mt] ) {                               /* 一時最大時刻が同じなら */
            count++;                                                 /* カウントを増やす */
        } else {                                                     /* 違ったら */
            mt = temp;                                               /* 最大時刻を更新して */
            count = 1;                                               /* カウントを１に戻す */
        }
        if( count == CHECK_INTERVAL && data[mt] != 0 ) {
            //            if( i > TERM - MINI_SIZE_TERM - CHECK_INTERVAL )       /* 最後の期間だけ */
            if( mt+1 != TERM ) {                                     /* 最後はいれず */
                ofs << mt+1 << SEPARATOR << data[mt] << ENDL;
            }
            mt = i + CHECK_INTERVAL - 1;
            count = 1;                                               /* カウントを１に戻す */
        }
    }

    return average_cycle( fname );                                  /* 平均周期を返す */
}
/*-----------------------------------------------------------------------------
 *
 *  計算結果出力
 *
 *-----------------------------------------------------------------------------*/


/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_Info
 * Description:  パラメータ情報を出力する
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: outputFile_Info( const char *fname ) const {
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    /*-----------------------------------------------------------------------------
     *  計算 前 情報
     *-----------------------------------------------------------------------------*/
    /* 設定 */
    OFSD( MATING_AGENT );
    /* 期間 */
    OFSV( OUTPUT_INTERVAL );                                         /* 出力期間 */
    OFSV( MINI_SIZE_TERM );                                          /* 拡大期間 */
    OFSV( WIDTH );                                                   /* 土地の幅 */
    /* エージェント */
    OFSV( INIT_NUM_A );                                              /* 初期エージェント数 */
    OFSV( MAX_NUM_A );                                               /* 最大エージェント数 */
    OFSV( MAX_VIRUS_AGENT_HAVE );                                    /* 最大保持ウイルス数 */
    OFSV( MAX_V_AGENT_INFECT_ONT_TIME );                             /* １期間最大感染ウイルス数 */
    OFSV( MAX_AGE );                                                 /* 寿命 */
    OFSV( BIRTH_RATE );                                              /* 出生率 */
    OFSV( BIRTH_AGE_FROM );                                          /* 出産適齢期 */
    OFSV( BIRTH_AGE_TO );
    OFSV( MOVE_DISTANCE );                                           /* 移動距離 */
    OFSV( INFECTION_RATE );                                          /* 感染率 */
    OFSV( INIT_INFECTED_RATIO );                                     /* 初期感染数 */
    /* ウイルス */
    OFSVP( NUM_V, admin_->virus_.size() );                           /* ウイルスの種類 */

    ITERATOR(Virus *) it_v = admin_->virus_.begin();
    while(it_v!=admin_->virus_.end()) {                              /* 各ウイルスの */
        OFSVP( V_LEN, (*it_v)->getLen() );                           /* タグ長 */
        it_v++;
    }
    /* ファイル名 */
    /*-----------------------------------------------------------------------------
     *  計算 後 情報
     *-----------------------------------------------------------------------------*/
    OFSVP( TERM, admin_->getTerm() );                                /* 計測器館 */
    OFSVP( NUM_A, admin_->agent_.size() );                           /* 最終エージェント数 */

#ifdef ___BENCHMARK
    OFSVP( TIME, Benchmark::Instance().getTime() );                  /* 計測時間 */
#endif
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_HasVirus( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* ファイルに出力 */
    FOR( j, admin_->virus_.size() ) {
        ofs << admin_->numHasVirus( *(admin_->virus_[j]) ) << SEPARATOR;                /* ウイルス j の保持者 */
    }
    int num_has_all = admin_->numHasAllVirus();
    ofs << num_has_all << SEPARATOR;                                 /* 全ウイルス保持者 */
    ofs << (double)num_has_all/admin_->agent_.size() << SEPARATOR;
    ofs << (double)admin_->numHasVirus( *(admin_->virus_[0]))/admin_->agent_.size() << ENDL;
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_HasImmunity
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_HasImmunity( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* ファイルに出力 */
    FOR( k, admin_->virus_.size() ) {
        ofs << admin_->numHasImmunity( *(admin_->virus_[k]) ) << SEPARATOR;             /* ウイルスに対する免疫獲得者数 */
    }
    int num_has_all = admin_->numHasAllImmunity();
    ofs << num_has_all << SEPARATOR;
    ofs << (double)num_has_all/admin_->agent_.size() << SEPARATOR;
    ofs << (double)admin_->numHasImmunity( *(admin_->virus_[0]) )/admin_->agent_.size() << ENDL;
}
/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_Population
 * Description:  人口推移を出力する
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_Population( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* 期間 */
    ofs << admin_->agent_.size() << SEPARATOR;                       /* 人口 */
    ofs << ENDL;
}
/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_InfectionContactRatio( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    double ratio = 0;
    int sum = 0;                                                     /* 何らかのウイルスに感染した接触回数 */

    ofs << admin_->getTerm() << SEPARATOR;                           /* 期間 */
    ofs << Monitor::Instance().getContactNum() << SEPARATOR;         /* 総接触数 */
    FOR( j, admin_->virus_.size() ) {                                                /* その内感染した回数 */
        sum += Monitor::Instance().getInfectionContactNum(admin_->virus_[j]);
        ofs << Monitor::Instance().getInfectionContactNum(admin_->virus_[j]) << SEPARATOR;
    }

    if( sum > 0 ) ratio
        = (double)sum / (double) Monitor::Instance().getContactNum(); 
    ofs << ratio << ENDL;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_LastLog( const char * )
 * Description:  最終、初期状態を出力
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: outputFile_LastLog( const char *fname ) const {
    static std::ofstream ofs(fname);
    ofs << "TERM:" << admin_->getTerm() << ENDL;
    ofs << "MAX_AGE:" << MAX_AGE << ENDL;
    ofs << "BIRTH_RATE:" << BIRTH_RATE << ENDL;
    ofs << "WIDTH:" << WIDTH << ENDL;
    ofs << "NUM_A:" << admin_->agent_.size() << ENDL;
    ofs << "INIT_NUM_A:" << INIT_NUM_A << ENDL;
    ofs << "NUM_V:" << admin_->virus_.size() << ENDL;
    ofs << "INFECTION_RATE:" << INFECTION_RATE << ENDL;
    ofs << "INIT_INFECTED_RATIO:" << INIT_INFECTED_RATIO << ENDL;
    ofs << "TAG_LEN_A:" << TAG_LEN_A << ENDL;
    ofs << "TAG_LEN_V:" << TAG_LEN_V << ENDL;
    FOR(i,admin_->virus_.size()) { ofs<<"["<<(*admin_->virus_[i]).getLen()<<"]:";
        FOR(j, (*admin_->virus_[i]).getLen()) { ofs<<int((*admin_->virus_[i]).tagAt(j)); } ofs<<ENDL;
        ofs << ">>> Agent Last Status" << ENDL;
        ITERATOR(Agent *) it_a = admin_->agent_.begin();
        while(it_a!=admin_->agent_.end()) {
            FOR(j, (*it_a)->getLen()) {
                ofs<<(*it_a)->tagAt(j);                                  /* エージェントのタグ */
            }
            ofs<<" "<<(*it_a)->numHoldingVirus();                        /* エージェントの保持ウイルス数 */
            ofs<<ENDL;
            it_a++;
        }
    }
}

/*-----------------------------------------------------------------------------
 *
 *  スクリプト系
 *
 *-----------------------------------------------------------------------------*/
/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: generatePlotScriptForPng()
 * Description:  png出力用の自動化スクリプトを生成
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: generatePlotScriptForPng() const
{

    std::ofstream ofs(AUTO_GPLOT_FILENAME);
    PLOT_STYLE;

    ofs << "set terminal png size "
        << IMG_SIZE << ENDL;
#if defined(AGING_AGENT) || defined(MATING_AGENT)
    // population
    scriptForPopulationPng(ofs);
#endif
    // hasVirus
    scriptForHasVirusPng(ofs);
    // hasImmunity
    scriptForHasImmunityPng(ofs);
    // SIR
    scriptForSIRPng(ofs);
    // contact
    scriptForContactPng(ofs);

    ofs << "set output" << ENDL;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  scriptFor***png
 *  Description:  画像を出力するスクリプト
 * =====================================================================================
 */
void FileFactory :: scriptForPopulationPng(std::ofstream &ofs) const {
    OFS_TITLE( Population, Term, Agent );
    OFS_PLOT( "Population.png" )
        << POPULATION_OUTPUT
        << LINE_STYLE
        << TITLE( population )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  Begin Term
     *-----------------------------------------------------------------------------*/
    OFS_TITLE( Population, Term, Agent );
    OFS_PLOT_PERIOD( "Population_mini.png", 0, MINI_SIZE_TERM )
        << POPULATION_OUTPUT
        << LINE_STYLE
        << TITLE( population )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  End Term
     *-----------------------------------------------------------------------------*/
    OFS_TITLE( Population, Term, Agent );
    OFS_PLOT_PERIOD( "Population_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << POPULATION_OUTPUT
        << LINE_STYLE
        << TITLE( population )
        << ENDL;
}
void FileFactory :: scriptForHasVirusPng(std::ofstream &ofs) const {

    OFS_TITLE( HasVirus, Term, Agent );

    OFS_PLOT( "HasVirus.png" )
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << TITLE( has_virus_0 )
        << ENDL;

    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasVirus.png" )
            << HAS_VIRUS_OUTPUT
            << USING(1, i+3)
            << LINE_STYLE
            << TITLE_N( has_virus_, i+1 )
            << ENDL;
    }

    OFS_REPLOT( "HasVirus.png" )
        << HAS_VIRUS_OUTPUT
        << USING( 1, admin_->virus_.size()+2 )
        << LINE_STYLE
        << TITLE( has_all_virus )
        << ENDL;
    /*-----------------------------------------------------------------------------
     *  Begin Term
     *-----------------------------------------------------------------------------*/
    OFS_TITLE( HasVirus, Term, Agent );

    OFS_PLOT_PERIOD( "HasVirus_mini.png", 0, MINI_SIZE_TERM)
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << TITLE( has_virus_0 )
        << ENDL;

    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasVirus_mini.png" )
            << HAS_VIRUS_OUTPUT
            << USING( 1, i+3 )
            << LINE_STYLE
            << TITLE_N( has_virus_, i+1 )
            << ENDL;
    }

    OFS_REPLOT( "HasVirus_mini.png" )
        << HAS_VIRUS_OUTPUT
        << USING( 1, admin_->virus_.size()+2 )
        << LINE_STYLE
        << TITLE( has_all_virus )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  End Term
     *-----------------------------------------------------------------------------*/
    double ave_p = outputFile_peakSearch( HAS_VIRUS_FNAME );         /* ピークサーチする */
    OFS_TITLE( HasVirus, Term, Agent );

    ofs << "set title \"HasVirus ( "
        << ave_p << " [term cycle] / "
        << averate_amplitude_ << " [amplitude])\""                   /* 周期を表示 */
        << ENDL;


    OFS_PLOT_PERIOD( "HasVirus_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << TITLE( has_virus_0 )
        << ENDL;
    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasVirus_last.png" )
            << HAS_VIRUS_OUTPUT
            << USING( 1, i+3 )
            << LINE_STYLE
            << TITLE_N( has_virus_, i+1 )
            << ENDL;
    }
    OFS_REPLOT( "HasVirus_last.png" )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << TITLE( has_all_virus )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  Peak
     *-----------------------------------------------------------------------------*/
    OFS_REPLOT( "HasVirus_last.png" )
        << QUO( "PEAK_A_hasVirus.txt" )                              /* ピーク */
        << LINE_STYLE_2
        << TITLE( peak )
        << ENDL;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: scriptForHasImmunityPng
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: scriptForHasImmunityPng(std::ofstream &ofs) const {

    OFS_TITLE( hasImmunity, Term, Agent );

    OFS_PLOT( "HasImmunity.png" )
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( has_immunity_0 )
        << ENDL;
    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasImmunity.png" )
            << HAS_IMMUNITY_OUTPUT
            << USING( 1, i+3 )
            << LINE_STYLE
            << TITLE_N( has_immunity_, i+1 )
            << ENDL;
    }
    OFS_REPLOT( "HasImmunity.png" )
        << HAS_IMMUNITY_OUTPUT
        << USING( 1, admin_->virus_.size()+2 )
        << LINE_STYLE
        << TITLE( has_all_immunity )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  Begin Term
     *-----------------------------------------------------------------------------*/
    OFS_PLOT_PERIOD( "HasImmunity_mini.png", 0, MINI_SIZE_TERM )
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( has_immunity_0 )
        << ENDL;

    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasImmunity_mini.png" )
            << HAS_IMMUNITY_OUTPUT
            << USING( 1, i+3 )
            << LINE_STYLE
            << TITLE_N( has_immunity_, i+1 )
            << ENDL;
    }
    OFS_REPLOT( "HasImmunity_mini.png" )
        << HAS_IMMUNITY_OUTPUT
        << USING( 1, admin_->virus_.size()+2 )
        << LINE_STYLE
        << TITLE( has_all_immunity )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  End Term XXX:
     *-----------------------------------------------------------------------------*/
    double ave_p = outputFile_peakSearch( HAS_IMMUNITY_FNAME );

    OFS_TITLE( hasImmunity, Term, Agent );
    ofs << "set title \"HasImmunity ( "
        << ave_p << " [term cycle] / "
        << averate_amplitude_ << " [amplitude])\"" /* 周期を表示 */
        << ENDL;

    OFS_PLOT_PERIOD( "HasImmunity_last.png", last_term_-MINI_SIZE_TERM, last_term_)
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( has_immunity_0 )
        << ENDL;

    FOR( i, admin_->virus_.size()-1 ) {
        OFS_REPLOT( "HasImmunity_last.png" )
            << HAS_IMMUNITY_OUTPUT
            << USING( 1, i+3 )
            << LINE_STYLE
            << TITLE_N( has_immunity_, i+1 )
            << ENDL;
    }
    OFS_REPLOT( "HasImmunity_last.png" )
        << HAS_IMMUNITY_OUTPUT
        << USING( 1, admin_->virus_.size()+2 )
        << LINE_STYLE
        << TITLE( has_all_immunity )
        << ENDL;

    /*-----------------------------------------------------------------------------
     *  Peak
     *-----------------------------------------------------------------------------*/
    OFS_REPLOT( "HasImmunity_last.png" )
        << QUO( "PEAK_A_hasImmunity.txt" )                           /* ピーク */
        << LINE_STYLE_2
        << TITLE( peak )
        << ENDL;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: scriptForSIRPng
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: scriptForSIRPng(std::ofstream &ofs) const {

    // SIR
    OFS_TITLE( SIR, Term, Agent );

    OFS_PLOT( "SIR.png" )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << TITLE( I )
        << ENDL;
    OFS_REPLOT( "SIR.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << " title " << "\"R\""
        << ENDL;

    // SIR_0
    OFS_TITLE( SIR_0, Term, Agent );

    OFS_PLOT( "SIR_0.png" )
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << " title " << "\"I_0\"" << ENDL;
    OFS_REPLOT( "SIR_0.png" )
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( R_0 )
        << ENDL;
    // SIR_RATIO
    OFS_TITLE( SIR_RATIO, Term, Ratio );
    OFSS( set yrange[0:1]; );

    OFS_PLOT( "SIR_RATIO.png" )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+3
        << LINE_STYLE
        << " title " << "\"I/POPULATION\""
        << ENDL;
    ofs << "set output \"SIR_RATIO.png\"" << ENDL;
    OFS_REPLOT( "SIR_RATIO.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+3 << LINE_STYLE
        << " title " << "\"R/POPULATION\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    // SIR_0_RATIO
    OFS_TITLE( SIR_0_RATIO, Term, Ratio );
    OFSS( set yrange[0:1]; );

    OFS_PLOT( "SIR_0_RATIO.png" )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+4 << LINE_STYLE
        << " title " << "\"I_0/POPULATION\""
        << ENDL;
    OFS_REPLOT( "SIR_0_RATIO.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+4 << LINE_STYLE
        << " title " << "\"R_0/POPULATION\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    /*-----------------------------------------------------------------------------
     *  Begin Term
     *-----------------------------------------------------------------------------*/
    // SIR_mini
    ofs << "set output \"SIR_mini.png\"" << ENDL;

    OFS_TITLE( SIR, Term, Agent );

    OFS_PLOT_PERIOD( "SIR_mini.png", 0, MINI_SIZE_TERM )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << " title " << "\"I\""
        << ENDL;
    OFS_REPLOT( "SIR_mini.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << " title " << "\"R\""
        << ENDL;

    // SIR_0_mini
    OFS_TITLE( SIR_0, Term, Agent );

    OFS_PLOT_PERIOD( "SIR_0_mini.png", 0, MINI_SIZE_TERM)
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << TITLE( I_0 )
        << ENDL;
    OFS_REPLOT( "SIR_0_mini.png" )
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( R_0 )
        << ENDL;

    // SIR_RATIO_mini
    OFS_TITLE( SIR_RATIO, Term, Ratio );
    OFSS( set yrange[0:1]; );

    OFS_PLOT_PERIOD( "SIR_RATIO_mini.png", 0, MINI_SIZE_TERM )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+3 << LINE_STYLE
        << " title " << "\"I/POPULATION\""
        << ENDL;
    OFS_REPLOT( "SIR_RATIO_mini.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+3 << LINE_STYLE
        << " title " << "\"R/POPULATION\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    // SIR_0_RATIO_mini
    OFS_TITLE( SIR_0_RATIO, Term, Ratio );
    OFSS( set yrange[0:1]; );

    OFS_PLOT_PERIOD( "SIR_0_RATIO_mini.png", 0, MINI_SIZE_TERM )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+4 << LINE_STYLE
        << " title " << "\"I_0/POPULATION\""
        << ENDL;
    OFS_REPLOT( "SIR_0_RATIO_mini.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+4
        << LINE_STYLE
        << " title " << "\"R_0/POPULATION\""
        << ENDL;
    OFSS( set autoscale y );

    /*-----------------------------------------------------------------------------
     *  End Term
     *-----------------------------------------------------------------------------*/
    // SIR_last
    ofs << "set output \"SIR_last.png\"" << ENDL;

    OFS_TITLE( SIR, Term, Agent );

    OFS_PLOT_PERIOD( "SIR_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << " title " << "\"I\""
        << ENDL;
    OFS_REPLOT( "SIR_last.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+2
        << LINE_STYLE
        << " title " << "\"R\""
        << ENDL;

    // SIR_0_last
    OFS_TITLE( SIR_0, Term, Agent );

    OFS_PLOT_PERIOD( "SIR_0_last.png", last_term_-MINI_SIZE_TERM, last_term_)
        << HAS_VIRUS_OUTPUT
        << LINE_STYLE
        << TITLE( I_0 )
        << ENDL;
    OFS_REPLOT( "SIR_0_last.png" )
        << HAS_IMMUNITY_OUTPUT
        << LINE_STYLE
        << TITLE( R_0 )
        << ENDL;

    // SIR_RATIO_last
    OFS_TITLE( SIR_RATIO, Term, Ratio );
    OFSS( set yrange[0:1] );

    OFS_PLOT_PERIOD( "SIR_RATIO_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+3
        << LINE_STYLE
        << " title " << "\"I/POPULATION\""
        << ENDL;
    OFS_REPLOT( "SIR_RATIO_last.png" )
        << HAS_IMMUNITY_OUTPUT
        << " using 1:" << admin_->virus_.size()+3 << LINE_STYLE
        << " title " << "\"R/POPULATION\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    // SIR_0_RATIO_last
    OFS_TITLE( SIR_0_RATIO, Term, Ratio );
    OFSS( set yrange[0:1] );

    OFS_PLOT_PERIOD( "SIR_0_RATIO_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << HAS_VIRUS_OUTPUT
        << " using 1:" << admin_->virus_.size()+4
        << LINE_STYLE
        << " title " << "\"I_0/POPULATION\""
        << ENDL;
    OFS_REPLOT( "SIR_0_RATIO_last.png" )
        << HAS_IMMUNITY_OUTPUT 
        << " using 1:" << admin_->virus_.size()+4
        << LINE_STYLE
        << " title " << "\"R_0/POPULATION\""
        << ENDL;
    OFSS( set autoscale y );

}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: scriptForContactPng
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: scriptForContactPng(std::ofstream &ofs) const {

    OFS_TITLE( InfectionContact, Term, Agent );

    OFS_PLOT( "Contact.png" )
        << CONTACT_OUTPUT << LINE_STYLE
        << " title \"contact\""
        << ENDL;
    FOR( i, admin_->virus_.size() ) {
        OFS_REPLOT( "Contact.png" )
            << CONTACT_OUTPUT
            << " using 1:" << i+3 << LINE_STYLE
            << " title " << "\"infect_contact_" << i+1 << "\""
            << ENDL;
    }

    OFS_TITLE( InfectionContactRatio, Term, Ratio );
    OFS_LINE( "set yrange[0:1]" );

    OFS_PLOT( "ContactRatio.png" )
        << CONTACT_OUTPUT << " using 1:" << admin_->virus_.size()+3
        << LINE_STYLE
        << " title \"ratio\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    /*-----------------------------------------------------------------------------
     *  Begin Term
     *-----------------------------------------------------------------------------*/
    OFS_TITLE( InfectionContact, Term, Agent );
    OFS_PLOT_PERIOD( "Contact_mini.png", 0, MINI_SIZE_TERM )
        << CONTACT_OUTPUT
        << LINE_STYLE
        << " title \"contact\""
        << ENDL;
    FOR( i, admin_->virus_.size() ) {
        OFS_REPLOT( "Contact_mini.png" )
            << CONTACT_OUTPUT
            << " using 1:" << i+3
            << LINE_STYLE
            << " title " << "\"infect_contact_" << i+1 << "\""
            << ENDL;
    }

    OFS_TITLE( InfectionContactRatio, Term, Ratio );
    OFS_LINE( "set yrange[0:1]" );

    OFS_PLOT_PERIOD( "ContactRatio_mini.png", 0, MINI_SIZE_TERM )
        << CONTACT_OUTPUT
        <<" using 1:" << admin_->virus_.size()+3
        << LINE_STYLE
        << " title \"ratio\""
        << ENDL;
    OFS_LINE( "set autoscale y" );

    /*-----------------------------------------------------------------------------
     *  End Term
     *-----------------------------------------------------------------------------*/
    OFS_TITLE( InfectionContact, Term, Agent );
    OFS_PLOT_PERIOD( "Contact_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << CONTACT_OUTPUT
        << LINE_STYLE
        << " title \"contact\""
        << ENDL;
    FOR( i, admin_->virus_.size() ) {
        OFS_REPLOT( "Contact_last.png" )
            << CONTACT_OUTPUT
            << " using 1:" << i+3
            << LINE_STYLE
            << " title " << "\"infect_contact_" << i+1 << "\""
            << ENDL;
    }

    OFS_TITLE( InfectionContactRatio, Term, Ratio );
    OFS_LINE( "set yrange[0:1]" );

    OFS_PLOT_PERIOD( "ContactRatio_last.png", last_term_-MINI_SIZE_TERM, last_term_ )
        << CONTACT_OUTPUT
        <<" using 1:" << admin_->virus_.size()+3
        << LINE_STYLE
        << " title \"ratio\""
        << ENDL;
    OFS_LINE( "set autoscale y" );
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: generateResultHtml()
 * Description:  結果をまとめて表示させるHTMLファイルを出力する
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: generateResultHtml( int t ) {
    if( t < MINI_SIZE_TERM ) last_term_ = MINI_SIZE_TERM;
    else last_term_ = t;

    std::ofstream ofs( FNAME_RESULT_HTML );

    /*-----------------------------------------------------------------------------
     *  目次
     *-----------------------------------------------------------------------------*/
    OFS( "<html><link rel=\"stylesheet\" href=\"result.css\"><body><font color=gray><code>" );
    OFS( "<h1><font color=black># 計算結果 "<<__DATE__<<", "<<__TIME__<<"</font></h1>" );
    OFS( "<ul>" );
    OFS( "<li><a href=#config>設定</a></li>" );
    OFS( "<li><a href=#population>人口</a></li>" );
    OFS( "<li><a href=#infection>感染者</a></li>" );
    OFS( "<li><a href=#immunity>免疫獲得者</a></li>" );
    OFS( "<li><a href=#sir>SIR</a></li>" );
    OFS( "<li><a href=#sir_0>SIR about virus_0</a></li>" );
    //    OFS( "<li><a href=#period>周期</a></li>" );
    OFS( "<li><a href=#contact>接触回数</a></li>" );
    OFS( "</ul>" );

    /*-----------------------------------------------------------------------------
     *  設定
     *-----------------------------------------------------------------------------*/
    OFSS(<h2 id=config>設定</h2>);

    OFSS(<div id="config">);
    OFSS(<div id="left">);
    // table
    OFSS( <table> );
#ifdef RANDOM_LOCATE                                                 /* 移動方法 */
    OFS_TD( "[ 移動 ]", "土地にランダムに再配置される" );
#else
    OFS_TD( "[ 移動 ]", "エージェントが指定された距離を各々移動する" );
#endif
#ifdef AGING_AGENT                                                   /* 老化 */
    OFS_TD( "[ 老化 ]", "する" );
#else
    OFS_TD( "[ 老化 ]", "しない" );
#endif
#ifdef MATING_AGENT                                                  /* 交配・出産 */
    OFS_TD( "[ 交配 ]", "する" );
#ifdef COUPLE_TAG                                                    /* 子供のタグ */
    OFS_TD( "[ 子供のタグ ]", "親のタグ（カップルタグ）を元に初期化" );
#else
    OFS_TD( "[ 子供のタグ ]", "ランダムに初期化" );
#endif
#else
    OFS_TD( "[ 交配 ]", "しない" );
#endif
    OFS_LINE( "</table>" );

    OFS_LINE( "<br />" );

    OFS_LINE( "<table class=\"center\"><tr>" );                      /* テーブル */
    OFS_LINE( "<th width=200px></th><th width=100px align=center>タグ長</th><th width=100px>数</th><th width=300px>取り付く位置<br />(左から012...)</th>" );
    OFS_LINE( "</tr>" );

    FOR( i, admin_->virus_.size() ) {                                /* ウイルスの種類を表示 */
        switch( (*admin_->virus_[i]).getSearchType() ) {
            case __NORMAL__:
                OFS_LINE( "<tr>" );
                OFS_LINE( "<td><font color=blue>通常ウイルス</td><td>"<<(*admin_->virus_[i]).getLen()
                        <<"</td><td>"<<1<<"</td>" );
                OFS_LINE( "</tr>" );
                break;
            case __FIXED__:
                OFS_LINE( "<tr>" );
                OFS_LINE( "<td><font color=blue>固定ウイルス</td><td>"<<(*admin_->virus_[i]).getLen()
                        <<"</td><td>"<<1
                        <<"</td><td>"<<(*admin_->virus_[i]).searchStartPoint(0) );
                OFS_LINE( "</tr>" );
                break;
            default:
                OFS_LINE( "<tr>" );
                OFS_LINE( "<td><font color=blue>---</td><td>---</td><td>---</td><td>" );
                OFS_LINE( "</tr>" );
                break;
        }
    }

    OFS_LINE( "<tr><td><font color=red>エージェント</td><td>"<<TAG_LEN_A
            <<"</td><td>"<<INIT_NUM_A<<"</td>" );
    OFS_LINE( "</tr></table>" );

    OFS_LINE( "<br />" );

    OFS_LINE( "<table>" );                                           /* テーブル */
    OFS_TD( "<font color=blue>ウイルスの感染確率</font>", INFECTION_RATE );
    OFS_TD( "<font color=blue>１期間で感染させるウイルスの最大数</font>", MAX_V_AGENT_INFECT_ONT_TIME );
    OFS_TD( "<font color=red>初期感染確率</font>", INIT_INFECTED_RATIO );
#if defined(AGING_AGENT) || defined( MATING_AGENT)
    OFS_TD( "<font color=red>エージェントの最大人数</font>", MAX_NUM_A );
#endif
#ifdef AGING_AGENT
    OFS_TD( "<font color=red>寿命</font>", MAX_AGE );
#endif
#ifdef MATING_AGENT
    OFS_TD( "<font color=red>出産確率</font>", BIRTH_RATE );
#endif
    OFS_TD( "土地の幅</font>", WIDTH );
    OFS_TD( "最大実行期間</font>", TERM );
#ifdef ___BENCHMARK
    OFS_TD( "計算時間( sec )</font>", Benchmark::Instance().getTime() );
#endif
    OFSS( </table> );

    OFSS( </div> );

    OFSS( <div id="right"> );                                         /* 注釈 */
    OFSS( <iframe src="note.html">注釈</iframe> );
    OFSS( </div> );
    OFSS( </div> );

#if defined(AGING_AGENT) || defined( MATING_AGENT)
    /*-----------------------------------------------------------------------------
     *  人口
     *-----------------------------------------------------------------------------*/
    OFS( "<h2 id=population>人口</h2>" );
    OFS_IMG_MINI( "Population.png", "Population_mini.png", "Population_last.png" );
    OFS( "</br>" );
    OFS( "population: エージェントの総人口" );
#endif

    /*-----------------------------------------------------------------------------
     *  感染者
     *-----------------------------------------------------------------------------*/
    OFS( "<h2 id=infection>感染者</h2>" );
    OFS_IMG_MINI( "HasVirus.png", "HasVirus_mini.png", "HasVirus_last.png" );
    FOR( i, admin_->virus_.size() ) {
        ofs << "<p>has_virus_" << i << ": "
            << "ウイルス " << i << " に感染しているエージェント数</p>" << ENDL;
    }
    ofs << "<p>has_all_virus" << "すべてのウイルスに感染しているエージェント数</p>" << ENDL;

    /*-----------------------------------------------------------------------------
     *  免疫獲得者
     *-----------------------------------------------------------------------------*/
    OFS( "<h2 id=immunity>免疫獲得者</h2>" );
    OFS_IMG_MINI( "HasImmunity.png", "HasImmunity_mini.png", "HasImmunity_last.png" );
    FOR( i, admin_->virus_.size() ) {
        ofs << "<p>has_virus_" << i << ": "
            << "ウイルス " << i << " への免疫を獲得しているエージェント数</p>" << ENDL;
    }
    ofs << "<p>has_all_virus" << "すべてのウイルスへの免疫を獲得しているエージェント数</p>" << ENDL;

    /*-----------------------------------------------------------------------------
     *  SIR
     *-----------------------------------------------------------------------------*/
    OFS( "<h2 id=sir>SIR</h2>" );
    OFS_IMG_MINI( "SIR.png", "SIR_mini.png", "SIR_last.png" );
    OFS( "I: すべてのウイルスに感染しているエージェント数" );
    OFS( "R: すべてのウイルスに対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_RATIO.png", "SIR_RATIO_mini.png", "SIR_RATIO_last.png" );
    OFS( "I/POPULATION: すべてのウイルスに感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: すべてのウイルスに対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS( "<h2 id=sir_0>SIR about virus_0</h2>" );
    OFS_IMG_MINI( "SIR_0.png", "SIR_0_mini.png", "SIR_0_last.png" );
    OFS( "I: ウイルス 0 に感染しているエージェント数" );
    OFS( "R: ウイルス 0 に対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_0_RATIO.png", "SIR_0_RATIO_mini.png", "SIR_0_RATIO_last.png" );
    OFS( "I/POPULATION: ウイルス 0 に感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: ウイルス 0 に対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );

    //    /*-----------------------------------------------------------------------------
    //     *  周期
    //     *-----------------------------------------------------------------------------*/
    //    OFS( "<h2 id=period>周期[ "<<PERIOD<<" ]</h2>" );
    //    ofs <<"<table class=\"graph\"><tr><td><img src=img/"
    //        << "AveGotNewImmunityPeriod.png" <<" /></td></tr><tr><td><img src=img/"
    //        << "GotNewEachImmunityPeriod.png" <<" /></td></tr>"
    //        << "</table><br />"<<ENDL;
    //    ofs << "<p>AveGotNewImmunityPeriod: " << "何らかのウイルスへの免疫を獲得した回数の平均</p>" << ENDL;
    //    FOR( i, admin_->virus_.size() ) {
    //        ofs << "<p>GotNewEachImmunityPeriod" << i << ": 先頭のエージェントが"
    //            << "ウイルス " << i << " への免疫を獲得した回数</p>" << ENDL;
    //    }
    //
    /*-----------------------------------------------------------------------------
     *  接触回数
     *-----------------------------------------------------------------------------*/
    OFS( "<h2 id=contact>接触回数</h2>" );
    OFS_IMG_MINI( "Contact.png", "Contact_mini.png", "Contact_last.png" );
    OFS( "contact: 総接触回数" );
    FOR( i, admin_->virus_.size() ) {
        ofs << "<p>infection_contact_" << i << ": "
            << "ウイルス " << i << " を感染させた接触回数</p>" << ENDL;
    }
    OFS_IMG_MINI( "ContactRatio.png", "ContactRatio_mini.png", "ContactRatio_last.png" );
    OFS( "ratio: 何らかのウイルスを感染させた接触回数 / 総接触回数" );
    OFS( "</code></html></body>" );
}
