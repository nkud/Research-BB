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

#define IMG_SIZE(w, h)          #w << "," << #h

#define OFS_STR(str)            do { ofs<< str << std::endl; }while(0);
#define OFS(str)                do { ofs<<str<<"<br />"<<std::endl; }while(0);
#define OFS_VAL(str,val)        do { ofs<<"[ "<<str<<" ]: "<<val<<"<br />"<<std::endl; }while(0);
#define OFS_IMG(img)            do { ofs<<"<br /><img src="<<#img<<" style=\"border:solid 1px gray;\"/><br />"<<std::endl; }while(0);
#define OFS_IMG_MINI(img,mini)  do { ofs<<"<br /><table><tr> \
                                <td><img src="<<#img<<" style=\"border:solid 1px gray;\"/></td></tr> \
                                <tr><td><img src="<<#mini<<" style=\"border:solid 1px gray;\"/></td> \
                                </tr></table><br />"<<std::endl; }while(0);
#define OFS_OUTPUT(str)         do { ofs<<"set output "<<#str<< std::endl; }while(0);
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
int Monitor :: getContactNum() const { return num_contact_; }        /* 接触回数を返す*/
int Monitor :: getInfectionContactNum( __TagInterface *t ) {
    return num_infection_contact_[ t ];                              /* 感染接触回数を返す */
}
Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;                                                 /* インスタンスを返す */
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: resetAll()
 * Description:  カウントをリセット
 *--------------------------------------------------------------------------------------
 */
void Monitor :: resetAll() {
    num_contact_ = 0;                                                /* 接触回数をリセット */

    num_infection_contact_.clear();                                  /* 感染接触回数をリセット */
}


/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: countUp *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Monitor :: countUpInfectionContact( __TagInterface *pv ) {
    num_infection_contact_[ pv ]++;                                  /* 指定のウイルスの感染接触回数をカウント */
}
void Monitor :: countUpContact() { num_contact_++; }                 /* 接触回数をカウント */

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
    std::ofstream ofs(AUTO_GPLOT_FILENAME);
    ofs << "set terminal png size "<< IMG_SIZE(1000, 250) << std::endl;
    // population
    scriptForPopulationPng(ofs);
    // hasVirus
    scriptForHasVirusPng(ofs);
    // hasImmunity
    scriptForHasImmunityPng(ofs);
    // SIR
    scriptForSIRPng(ofs);
    // contact
    scriptForContactPng(ofs);
    ofs << "set output" << std::endl;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  scriptFor***png
 *  Description:  画像を出力するスクリプト
 * =====================================================================================
 */
void scriptForPopulationPng(std::ofstream &ofs) {
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set output \"Population.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl;
    ofs << "plot " << POPULATION_OUTPUT << " w l"
        << " title " << "\"population\"" << std::endl;
    // Mini size
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set output \"Population_mini.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl;
    ofs << "plot " << POPULATION_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title " << "\"population\"" << std::endl;
}
void scriptForHasVirusPng(std::ofstream &ofs) {
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
    // Mini size
    ofs << "set output \"HasVirus_mini.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"HasVirus\"" << std::endl
        << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM <<" w l"
        << " title " << "\"has_virus_" << 0 << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasVirus_mini.png\"" << std::endl;
        ofs << "replot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_virus_" << i+1 << std::endl;
    }
    ofs << "set output \"HasVirus_mini.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_virus\"" << std::endl;
}
void scriptForHasImmunityPng(std::ofstream &ofs) {
    OFS_OUTPUT( "HasImmunity.png" );
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
    OFS_OUTPUT( "HasImmunity.png" );
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
    // Mini Size
    OFS_OUTPUT( "HasImmunity_mini.png" );
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"hasImmunity\"" << std::endl
        << "plot "<< HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title \"has_immunity_0\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasImmunity_mini.png\"" << std::endl;
        ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"HasImmunity_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
}
void scriptForSIRPng(std::ofstream &ofs) {
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
    // Mini Size
    ofs << "set output \"SIR_mini.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"SIR\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output \"SIR_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"R\"" << std::endl;

    // SIR_0
    ofs << "set output \"SIR_0_mini.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"SIR_0\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title " << "\"I_0\"" << std::endl;
    ofs << "set output \"SIR_0_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<< " w l"
        << " title " << "\"R_0\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"SIR_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<< MINI_SIZE_TERM
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_STR( "set autoscale y" );
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::" << MINI_SIZE_TERM
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I_0/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R_0/POPULATION\"" << std::endl;
    OFS_STR( "set autoscale y" );
}
void scriptForContactPng(std::ofstream &ofs) {
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
    // Mini Size
    ofs << "set output \"Contact_mini.png\"" << std::endl;
    OFS_STR ( "set yl \"Agent\"" );
    OFS_STR ( "set xl \"Term\"" );
    ofs << "set title \"InfectionContact\"" << std::endl
        << "plot "<< CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title \"contact\"" << std::endl;
    FOR( i, NUM_V ) {
        ofs << "set output \"Contact_mini.png\"" << std::endl;
        ofs << "replot " << CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
            << " using 1:" << i+3 << " w l"
            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"ContactRatio_mini.png\"" << std::endl;
    OFS_STR ( "set yl" );
    OFS_STR ( "set xl \"Term\"" );
    OFS_STR( "set yrange[0:1]" );
    ofs << "set title \"InfectionContactRatio\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    OFS_STR( "set autoscale y" );
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
    OFS_TD( "<font color=blue>ウイルスのタグ長</font>", "<font color=blue>"<<TAG_LEN_V<<"</font>" );
    OFS_TD( "<font color=blue>ウイルスの数</font>", NUM_V );
    OFS_TD( "<font color=blue>ウイルスの感染確率</font>", INFECTION_RATE );
    OFS_TD( "<font color=blue>１期間で感染させるウイルスの最大数</font>", MAX_V_AGENT_INFECT_ONT_TIME );
    OFS_TD( "<font color=red>エージェントのタグ長</font>", "<font color=red>"<<TAG_LEN_A<<"</font>" );
    OFS_TD( "<font color=red>エージェントの初期人数</font>", INIT_NUM_A );
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
#ifdef __unix__
    OFS_TD( "実行期間</font>", Benchmark::Instance().getTime() );
#endif
    OFS_STR( "</table>" );
    OFS( "<hr>" );

#if defined(AGING_AGENT) || defined( MATING_AGENT)
    // 人口
    OFS( "<h2>人口</h2>" );
    OFS_IMG_MINI( "Population.png", "Population_mini.png" );
    OFS( "</br>" );
    OFS( "population: エージェントの総人口" );
    OFS( "<hr>" );
#endif
    // 感染者
    OFS( "<h2>感染者</h2>" );
    OFS_IMG_MINI( "HasVirus.png", "HasVirus_mini.png" );
    FOR( i, NUM_V ) {
        ofs << "has_virus_" << i << ": "
            << "ウイルス " << i << " に感染しているエージェント数<br />" << std::endl;
    }
    ofs << "has_all_virus" << "すべてのウイルスに感染しているエージェント数" << std::endl;
    OFS( "<hr>" );
    // 免疫獲得者
    OFS( "<h2>免疫獲得者</h2>" );
    OFS_IMG_MINI( "HasImmunity.png", "HasImmunity_mini.png" );
    FOR( i, NUM_V ) {
        ofs << "has_virus_" << i << ": "
            << "ウイルス " << i << " への免疫を獲得しているエージェント数<br />" << std::endl;
    }
    ofs << "has_all_virus" << "すべてのウイルスへの免疫を獲得しているエージェント数" << std::endl;
    OFS( "<hr>" );
    // SIR
    OFS( "<h2>SIR</h2>" );
    OFS_IMG_MINI( "SIR.png", "SIR_mini.png" );
    OFS( "I: すべてのウイルスに感染しているエージェント数" );
    OFS( "R: すべてのウイルスに対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_RATIO.png", "SIR_RATIO_mini.png" );
    OFS( "I/POPULATION: すべてのウイルスに感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: すべてのウイルスに対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS_IMG_MINI( "SIR_0.png", "SIR_0_mini.png" );
    OFS( "I: ウイルス 0 に感染しているエージェント数" );
    OFS( "R: ウイルス 0 に対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_0_RATIO.png", "SIR_0_RATIO_mini.png" );
    OFS( "I/POPULATION: ウイルス 0 に感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: ウイルス 0 に対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS( "<hr>" );
    // 接触回数
    OFS( "<h2>接触回数</h2>" );
    OFS_IMG_MINI( "Contact.png", "Contact_mini.png" );
    OFS( "contact: 総接触回数" );
    FOR( i, NUM_V ) {
        ofs << "infection_contact_" << i << ": "
            << "ウイルス " << i << " を感染させた接触回数<br />" << std::endl;
    }
    OFS_IMG_MINI( "ContactRatio.png", "ContactRatio_mini.png" );
    OFS( "ratio: 何らかのウイルスを感染させた接触回数 / 総接触回数" );
    OFS( "</code></html></body>" );
}

#ifdef __unix__
/*
 *--------------------------------------------------------------------------------------
 *      Method:  Benchmark :: *
 * Description:  実行時間を表示( unix only )
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
