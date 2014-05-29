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
#include "AgentCounter.h"
#include "Virus.h"
#include "VirusCounter.h"
#include "Global.h"
#include "Benchmark.h"

#define AUTO_GPLOT_FILENAME     "auto.plt"
#define FNAME_RESULT_HTML       "RESULT.html"

/*-----------------------------------------------------------------------------
 *  マクロ
 *-----------------------------------------------------------------------------*/
#define OFSV(str)                         do { ofs << #str << "," << (str) << std::endl; }while(0);
#define OFSVP(str,val)                    do { ofs << #str << "," << (val) << std::endl; }while(0);
#define OFSVV(str1,str2)                  do { ofs << #str1 << "," << #str2 << std::endl; }while(0);

#define ENDL                            std::endl

/*-----------------------------------------------------------------------------
 *  スタイル
 *-----------------------------------------------------------------------------*/
//#define LINE_STYLE                      " with l lw 2 "
//#define LINE_STYLE_2                    " with i lt 0 lw 2 "
//#define LINE_STYLE_2                    " with p ps 2 pt 4 "

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

    int t = admin_->getTerm();                                       /* 計算後実行期間 */
    int last_term;
    if( t < MINI_SIZE_TERM ) last_term = MINI_SIZE_TERM;
    else last_term = t;

    /*-----------------------------------------------------------------------------
     *  計算 前 情報
     *-----------------------------------------------------------------------------*/
    /* 設定 */
    /* 期間 */
    OFSV( OUTPUT_INTERVAL );                                         /* 出力期間 */
    OFSV( MINI_SIZE_TERM );                                          /* 拡大期間 */
    OFSV( WIDTH );                                                   /* 土地の幅 */
    /* エージェント */
    OFSVP( A_LEN, (*admin_->agent())[0]->getLen() );                 /* エージェントのタグ長 */
    OFSV( A_INIT_NUM );                                              /* 初期エージェント数 */
    OFSV( A_MAX_NUM );                                               /* 最大エージェント数 */
    OFSV( A_MAX_V_CAN_HAVE );                                        /* 最大保持ウイルス数 */
    OFSV( A_MAX_V_INFECTED_ONE_TERM );                               /* １期間最大感染ウイルス数 */
    OFSV( A_MAX_AGE );                                               /* 寿命 */
    OFSV( A_BIRTH_RATE );                                            /* 出生率 */
    OFSV( A_BIRTH_AGE_FROM );                                        /* 出産適齢期 */
    OFSV( A_BIRTH_AGE_TO );
    OFSV( A_MOVE_DISTANCE );                                         /* 移動距離 */
    OFSV( INFECTION_RATE );                                          /* 感染率 */
    OFSV( A_INIT_INFECTED_RATE );                                    /* 初期感染数 */
    /* ウイルス */
    OFSVP( V_NUM, (*admin_->virus()).size() );                       /* ウイルスの種類 */

    ITERATOR(Virus *) it_v = admin_->getVirusIteratorBegin();
    while(it_v != admin_->getVirusIteratorEnd()) {                   /* 各ウイルスの */
        ofs << "V_LEN[ "<<*it_v<<" ],";                              /* タグ長 */
        ofs << (*it_v)->getLen() << ENDL;

        ofs << "V_TAG[ "<<*it_v<<" ],";                              /* タグ */
        FOR(j, (*it_v)->getLen()) {
            ofs<<int((*it_v)->tagAt(j));
        } ofs<<ENDL;
        it_v++;
    }
    /* ファイル名 */
    OFSVV( FNAME_HAS_VIRUS, A_hasVirus.txt )                         /* ファイル名 */
    OFSVV( FNAME_HAS_IMMUNITY, A_hasImmunity.txt )
    OFSVV( FNAME_CONTACT, A_infectionContact.txt )
    OFSVV( FNAME_POPULATION, A_population.txt )
    /* その他情報 */
    OFSVP( L_POPULATION_DENSITY[%], (double)A_INIT_NUM / ( WIDTH*WIDTH ) * 100 );
    /*-----------------------------------------------------------------------------
     *  計算 後 情報
     *-----------------------------------------------------------------------------*/
    OFSVP( TERM, admin_->getTerm() );                                /* 計測器館 */
    OFSVP( A_NUM, admin_->getAgentSize() );                          /* 最終エージェント数 */
    OFSVP( LAST_TERM, last_term );                                   /* 実行期間 */
#ifdef AGING_AGENT
    OFSVP( AGING_AGENT, 1 );
#else
    OFSVP( AGING_AGENT, 0 );
#endif
#ifdef MATING_AGENT
    OFSVP( MATING_AGENT, 1 );
#else
    OFSVP( MATING_AGENT, 0 );
#endif
#ifdef NO_DIAGONAL
    OFSVP( NO_DIAGONAL, 1 );
#else
    OFSVP( NO_DIAGONAL, 0 );
#endif
#ifdef ___BENCHMARK
    OFSVP( TIME, Benchmark::Instance().getTime() );                  /* 計測時間 */
#endif
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_VirusVariaty( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* ファイルに出力 */
    ofs << VirusCounter::Instance().getVirusVariaty() << ENDL;
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
    FOR( j, admin_->getVirusSize() ) {                                /* ウイルスの数だけ */
        ofs << admin_->numHasVirus( *(admin_->virus(j)) ) << SEPARATOR;                /* ウイルス j の保持者 */
    }
    int num_has_all = admin_->numHasAllVirus();                      /* 全ウイルスに対する免疫獲得者 */
    ofs << num_has_all << SEPARATOR;                                 /* 全ウイルス保持者 */
    ofs << (double)num_has_all/admin_->getAgentSize() << SEPARATOR;
    ofs << (double)admin_->numHasVirus( *(admin_->virus(0)))/admin_->getAgentSize() << ENDL;
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
    FOR( k, admin_->getVirusSize() ) {
        ofs << admin_->numHasImmunity( *(admin_->virus(k)) ) << SEPARATOR;             /* ウイルスに対する免疫獲得者数 */
    }
    int num_has_all = admin_->numHasAllImmunity();
    ofs << num_has_all << SEPARATOR;
    ofs << (double)num_has_all/admin_->getAgentSize() << SEPARATOR;
    ofs << (double)admin_->numHasImmunity( *(admin_->virus(0)) )/admin_->getAgentSize() << ENDL;
}
/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_Population
 * Description:  人口推移を出力する
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_Population( const char *fname ) const {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* 期間 */
    ofs << admin_->getAgentSize() << SEPARATOR;                       /* 人口 */
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
    ofs << AgentCounter::Instance().getCountContact() << SEPARATOR;         /* 総接触数 */
    sum = AgentCounter::Instance().getCountInfectionContact();
    FOR( j, admin_->getVirusSize() ) {                                                /* その内感染した回数 */
//        ofs << Monitor::Instance().getInfectionContactNum(admin_->virus(j)) << SEPARATOR;
    }

    if( sum > 0 ) ratio
        = (double)sum / (double) AgentCounter::Instance().getCountContact(); 
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
    ofs << "MAX_AGE:" << A_MAX_AGE << ENDL;
    ofs << "BIRTH_RATE:" << A_BIRTH_RATE << ENDL;
    ofs << "WIDTH:" << WIDTH << ENDL;
    ofs << "NUM_A:" << admin_->getAgentSize() << ENDL;
    ofs << "A_INIT_NUM:" << A_INIT_NUM << ENDL;
    ofs << "NUM_V:" << admin_->getVirusSize() << ENDL;
    ofs << "INFECTION_RATE:" << INFECTION_RATE << ENDL;
    ofs << "INIT_INFECTED_RATIO:" << A_INIT_INFECTED_RATE << ENDL;
    ofs << "TAG_LEN_A:" << A_DEFAULT_LEN << ENDL;
    ofs << "TAG_LEN_V:" << V_DEFAULT_LEN << ENDL;
    FOR(i,admin_->getVirusSize()) { ofs<<"["<<(*admin_->virus(i)).getLen()<<"]:";
        FOR(j, (*admin_->virus(i)).getLen()) { ofs<<int((*admin_->virus(i)).tagAt(j)); } ofs<<ENDL;
    }
    ofs << ">>> Agent Last Status" << ENDL;
    ITERATOR(Agent *) it_a = admin_->getAgentIteratorBegin();
    while(it_a!=admin_->getAgentIteratorEnd()) {
        FOR(j, (*it_a)->getLen()) {
            ofs<<(*it_a)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs<<" "<<(*it_a)->numHoldingVirus();                        /* エージェントの保持ウイルス数 */
        ofs<<ENDL;
        it_a++;
    }
    ofs << ">>> Virus Data Base Last Status" << ENDL;
    ITERATOR(Virus*) it_v = VirusCounter::Instance().getVirusDataBaseIteratorBegin();
    while(it_v!=VirusCounter::Instance().getVirusDataBaseIteratorEnd()) {
        FOR(j, (*it_v)->getLen()) {
            ofs<<(*it_v)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs<<ENDL;
        it_v++;
    }
}
void FileFactory :: outputFile_LastVirusDataBase( const char *fname ) const {
    std::ofstream ofs(fname);
    ITERATOR(Virus*) it_v = VirusCounter::Instance().getVirusDataBaseIteratorBegin();
    while(it_v!=VirusCounter::Instance().getVirusDataBaseIteratorEnd()) {
        FOR(j, (*it_v)->getLen()) {
            ofs<<(*it_v)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs<<ENDL;
        it_v++;
    }
    ofs.close();
}
/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_peakSearch()
 * Description:  ピークサーチする
 *--------------------------------------------------------------------------------------
 */
static int max_term_in_interval( const int data[], int cursor, int len ) {
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

static double average_cycle( const char *origin_fname ) {
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
    int vmin = A_INIT_NUM;
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

