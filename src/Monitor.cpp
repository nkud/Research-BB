/*
 * =====================================================================================
 *
 *       Filename:  Monitor.cpp
 *
 *    Description:  モニター、ベンチマーク
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#include "Monitor.h"
#include "Global.h"
#include <fstream>
#include <iostream>

#define GPLOT_FILENAME          "quick.plt"
#define AUTO_GPLOT_FILENAME     "auto.plt"
#define FNAME_RESULT_HTML       "RESULT.html"

#define OFS_STR(str)            do { ofs<< str << std::endl; }while(0);
#define OFS(str)                do { ofs<<str<<"<br />"<<std::endl; }while(0);
#define OFS_VAL(str,val)        do { ofs<<"[ "<<str<<" ]: "<<val<<"<br />"<<std::endl; }while(0);
#define OFS_IMG(str)            do { ofs<<"<br /><img src="<<#str<<" style=\"border:solid 1px gray;\"/><br />"<<std::endl; }while(0);
#define OFS_TD(str,val)         do { ofs<<"<tr><td>"<<str<<"</td>"<<"<td>"<<val<<"</td></tr>"<<std::endl; }while(0);

#define HAS_VIRUS_OUTPUT        "\"A_hasVirus.txt\""
#define HAS_IMMUNITY_OUTPUT     "\"A_hasImmunity.txt\""
#define CONTACT_OUTPUT          "\"A_infectionContact.txt\""
#define POPULATION_OUTPUT       "\"A_population.txt\""

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: *
 * Description:  ゲッタ
 *--------------------------------------------------------------------------------------
 */
int Monitor :: getContactNum() const { return num_contact_; }
int Monitor :: getInfectionContactNum( __TagInterface *t ) { return num_infection_contact_[ t ]; }
Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: resetAll()
 * Description:  カウントをリセット
 *--------------------------------------------------------------------------------------
 */
void Monitor :: resetAll() {
    num_contact_ = 0;

    num_infection_contact_.clear();
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: countUp *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Monitor :: countUpInfectionContact( __TagInterface *pv ) {
    num_infection_contact_[ pv ]++;
}
void Monitor :: countUpContact() { num_contact_++; }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: generatePlotScript()
 * Description:  プロット用のスクリプトを生成
 *--------------------------------------------------------------------------------------
 */
void Monitor :: generatePlotScript() {
    std::ofstream ofs(GPLOT_FILENAME);
#ifdef OUTPUT_POPULATION
    ofs << "set title \"Population\" font \"helvetica, 24\"" << std::endl
        << "plot " << POPULATION_OUTPUT << " w l"
        << " title " << "\"population\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
#endif
#ifdef OUTPUT_HAS_VIRUS
    ofs << "set title \"ウイルス保持者\" font \"helvetica, 24\"" << std::endl
        << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"ウイルス" << 0 << "保持\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "replot " << HAS_VIRUS_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"ウイルス" << i+1 << "保持\"" << std::endl;
    }
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"全ウイルス保持\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
#endif
#ifdef OUTPUT_HAS_IMMUNITY
    // hasImmunity
    ofs << "set title \"hasImmunity\" font \"helvetica, 24\"" << std::endl
        << "plot "<< HAS_IMMUNITY_OUTPUT << " w l"
        << " title \"has_immunity_0\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "replot " << HAS_IMMUNITY_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
    }
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
#endif
#ifdef OUTPUT_SIR
    // SIR
    ofs << "set title \"SIR\" font \"helvetica, 24\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;

    // SIR_0
    ofs << "set title \"SIR_0\" font \"helvetica, 24\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
    // SIR_RATIO
    ofs << "set title \"SIR_RATIO\" font \"helvetica, 24\"" << std::endl;
    OFS_STR( "set yrange[0:1]" );
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_STR ( "set autoscale y" );
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
    // SIR_0_RATIO
    ofs << "set title \"SIR_0_RATIO\" font \"helvetica, 24\"" << std::endl;
    OFS_STR( "set yrange[0:1]" );
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_STR ( "set autoscale y" );
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
#endif
#ifdef OUTPUT_CONTACT
    // contact
    ofs << "set title \"infectioncontact\" font \"helvetica, 24\"" << std::endl
        << "plot "<< CONTACT_OUTPUT << " w l"
        << " title \"contact\"" << std::endl;
    FOR( i, NUM_V ) {
        ofs << "replot " << CONTACT_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"infection_contact_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;

    ofs << "set title \"infectioncontactratio\" font \"helvetica, 24\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
#endif
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: generatePlotScriptForPng()
 * Description:  png出力用の自動化スクリプトを生成
 *--------------------------------------------------------------------------------------
 */
void Monitor :: generatePlotScriptForPng() {
    // population
    std::ofstream ofs(AUTO_GPLOT_FILENAME);
    ofs << "set terminal png" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set output \"Population.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl
        << "plot " << POPULATION_OUTPUT << " w l"
        << " title " << "\"population\"" << std::endl;
    // hasVirus
    ofs << "set output \"HasVirus.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"HasVirus\"" << std::endl
        << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"has_virus_" << 0 << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasVirus.png\"" << std::endl;
        ofs << "replot " << HAS_VIRUS_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_virus_" << i+1 << std::endl;
    }
    ofs << "set output \"HasVirus.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_virus\"" << std::endl;
    // hasImmunity
    ofs << "set output \"HasImmunity.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"hasImmunity\"" << std::endl
        << "plot "<< HAS_IMMUNITY_OUTPUT << " w l"
        << " title \"has_immunity_0\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasImmunity.png\"" << std::endl;
        ofs << "replot " << HAS_IMMUNITY_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"HasImmunity.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
    // SIR
    ofs << "set output \"SIR.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"SIR\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output \"SIR.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"R\"" << std::endl;

    // SIR_0
    ofs << "set output \"SIR_0.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"SIR_0\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"I_0\"" << std::endl;
    ofs << "set output \"SIR_0.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " w l"
        << " title " << "\"R_0\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"SIR_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_STR( "set autoscale y" );
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I_0/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R_0/POPULATION\"" << std::endl;
    OFS_STR( "set autoscale y" );
    // contact
    ofs << "set output \"Contact.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"InfectionContact\"" << std::endl
        << "plot "<< CONTACT_OUTPUT << " w l"
        << " title \"contact\"" << std::endl;
    FOR( i, NUM_V ) {
        ofs << "set output \"Contact.png\"" << std::endl;
        ofs << "replot " << CONTACT_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"ContactRatio.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"InfectionContactRatio\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    OFS_STR( "set autoscale y" );
    ofs << "set output" << std::endl;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: generateResultHtml()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Monitor :: generateResultHtml() {
    std::ofstream ofs( FNAME_RESULT_HTML );
    OFS( "<html><body><font color=gray><code>" );
    OFS( "<h1><font color=black>計算結果</font></h1>" );
    OFS( "<h2>設定</h2>" );
    // table
    OFS_STR( "<table style=\"border:solid 1px gray\"; width=640px>" );
#ifdef RANDOM_LOCATE                                                 /* 移動方法 */
    OFS_TD( "[ 移動 ]", "土地にランダムに再配置される" );
#else
    OFS_TD( "[ 移動 ]", "エージェントが指定された距離をランダムに移動する" );
#endif
#ifdef AGING_AGENT                                                   /* 老化 */
    OFS_TD( "[ 老化 ]", "有" );
#else
    OFS_TD( "[ 老化 ]", "無" );
#endif
#ifdef MATING_AGENT                                                  /* 交配・出産 */
    OFS_TD( "[ 交配 ]", "有" );
#ifdef COUPLE_TAG                                                    /* 子供のタグ */
    OFS_TD( "[ 子供のタグ ]", "カップルタグ" );
#else
    OFS_TD( "[ 子供のタグ ]", "両親のタグ" );
#endif
#else
    OFS_TD( "[ 交配 ]", "無" );
#endif
    OFS_TD( "<font color=blue>ウイルスの数</font>", NUM_V );
    OFS_TD( "<font color=blue>ウイルスのタグ長</font>", TAG_LEN_V );
    OFS_TD( "<font color=blue>ウイルスの感染確率</font>", INFECTION_RATE );
    OFS_TD( "<font color=red>エージェントの初期人数</font>", INIT_NUM_A );
    OFS_TD( "<font color=red>エージェントの最大人数</font>", MAX_NUM_A );
    OFS_TD( "<font color=red>エージェントのタグ長</font>", TAG_LEN_A );
    OFS_TD( "<font color=red>寿命</font>", MAX_AGE );
    OFS_TD( "<font color=red>出産確率</font>", BIRTH_RATE );
    OFS_TD( "初期感染確率</font>", INIT_INFECTED_RATIO );
    OFS_TD( "土地の幅</font>", WIDTH );
    OFS_TD( "最大実行期間</font>", TERM );
#ifdef __unix__
    OFS_TD( "実行期間</font>", Benchmark::Instance().getTime() );
#endif
    OFS_STR( "</table>" );
    OFS( "<hr>" );

#if defined(AGING_AGENT) || defined( MATING_AGENT)
    // 人口
    OFS( "<h2>人口</h2>" );
    OFS_IMG( "Population.png" );
    OFS( "</br>" );
    OFS( "population: エージェントの総人口" );
    OFS( "<hr>" );
#endif
    // 感染者
    OFS( "<h2>感染者</h2>" );
    OFS_IMG( "HasVirus.png" );
    FOR( i, NUM_V ) {
        ofs << "has_virus_" << i << ": "
            << "ウイルス " << i << " に感染しているエージェント数<br />" << std::endl;
    }
    ofs << "has_all_virus" << "すべてのウイルスに感染しているエージェント数" << std::endl;
    OFS( "<hr>" );
    // 免疫獲得者
    OFS( "<h2>免疫獲得者</h2>" );
    OFS_IMG( "HasImmunity.png" );
    FOR( i, NUM_V ) {
        ofs << "has_virus_" << i << ": "
            << "ウイルス " << i << " への免疫を獲得しているエージェント数<br />" << std::endl;
    }
    ofs << "has_all_virus" << "すべてのウイルスへの免疫を獲得しているエージェント数" << std::endl;
    OFS( "<hr>" );
    // SIR
    OFS( "<h2>SIR</h2>" );
    OFS_IMG( "SIR.png" );
    OFS( "I: すべてのウイルスに感染しているエージェント数" );
    OFS( "R: すべてのウイルスに対して免疫を獲得しているエージェント数" );
    OFS_IMG( "SIR_RATIO.png" );
    OFS( "I/POPULATION: すべてのウイルスに感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: すべてのウイルスに対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS_IMG( "SIR_0.png" );
    OFS( "I: ウイルス 0 に感染しているエージェント数" );
    OFS( "R: ウイルス 0 に対して免疫を獲得しているエージェント数" );
    OFS_IMG( "SIR_0_RATIO.png" );
    OFS( "I/POPULATION: ウイルス 0 に感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: ウイルス 0 に対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS( "<hr>" );
    // 接触回数
    OFS( "<h2>接触回数</h2>" );
    OFS_IMG( "Contact.png" );
    OFS( "contact: 総接触回数" );
    FOR( i, NUM_V ) {
        ofs << "infection_contact_" << i << ": "
            << "ウイルス " << i << " を感染させた接触回数<br />" << std::endl;
    }
    OFS_IMG( "ContactRatio.png" );
    OFS( "ratio: 何らかのウイルスを感染させた接触回数 / 総接触回数" );
    OFS( "</code></html></body>" );
}

#ifdef __unix__
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Benchmark :: *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
Benchmark& Benchmark :: Instance() {
    static Benchmark bm;
    return bm;
}
void Benchmark :: startTimer() {
    gettimeofday(&tv_, NULL);
    start_ = tv_.tv_sec + tv_.tv_usec * 1e-6;
}
void Benchmark :: stopTimer() {
    gettimeofday(&tv_, NULL);
    end_ = tv_.tv_sec + tv_.tv_usec * 1e-6;
}
double Benchmark :: getTime() const {
    return end_ - start_;
}
void Benchmark :: printTime() const {
    std::cout << "[ time ]: " << end_ - start_ << " sec" << std::endl;
}
void Benchmark :: printElapsedTime() {
    gettimeofday(&tv_, NULL);
    double now = tv_.tv_sec + tv_.tv_usec * 1e-6;
    std::cout << "[ elapsed time ]: " << now - start_ << " sec" << std::endl;
}
#endif
