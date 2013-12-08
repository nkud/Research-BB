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
#include "Agent.h"
#include "Virus.h"

#include <fstream>
#include <iostream>

#define GPLOT_FILENAME          "quick.plt"
#define AUTO_GPLOT_FILENAME     "auto.plt"
#define FNAME_RESULT_HTML       "RESULT.html"

#define IMG_SIZE(w, h)          #w << "," << #h

#define EVERY_LAST(t)           " every ::"<< t-MINI_SIZE_TERM<<"::"<<t<<" "

#define OFS(str)                do { ofs<<"<p>"<<str<<"</p>"<<std::endl; }while(0);
#define OFS_LINE(str)           do { ofs<< str << std::endl; }while(0);
#define OFS_VAL(str,val)        do { ofs<<"[ "<<str<<" ]: "<<val<<"<br />"<<std::endl; }while(0);
#define OFS_IMG(img)            do { ofs<<"<br /><img src=img/"<<#img<<" /><br />"<<std::endl; }while(0);
#define OFS_IMG_MINI(img,mini,last)  do { ofs<<"<table class=\"graph\"><tr> \
                                <td><img src=img/"<<img<<" /></td></tr><tr> \
                                <td><img src=img/"<<mini<<" /></td></tr><t> \
                                <td><img src=img/"<<last<<" /></td></tr> \
                                </table><br />"<<std::endl; }while(0);
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

///*
// *--------------------------------------------------------------------------------------
// *      Method:  Monitor :: generatePlotScript()
// * Description:  プロット用のスクリプトを生成
// *--------------------------------------------------------------------------------------
// */
//void Monitor :: generatePlotScript() {
//    std::ofstream ofs(GPLOT_FILENAME);
//#ifdef OUTPUT_POPULATION
//    ofs << "set title \"Population\" font \"helvetica, 24\"" << std::endl
//        << "plot " << POPULATION_OUTPUT << " w l"
//        << " title " << "\"population\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//#endif
//#ifdef OUTPUT_HAS_VIRUS
//    ofs << "set title \"ウイルス保持者\" font \"helvetica, 24\"" << std::endl
//        << "plot " << HAS_VIRUS_OUTPUT << " w l"
//        << " title " << "\"ウイルス" << 0 << "保持\"" << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "replot " << HAS_VIRUS_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"ウイルス" << i+1 << "保持\"" << std::endl;
//    }
//    ofs << "replot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"全ウイルス保持\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//#endif
//#ifdef OUTPUT_HAS_IMMUNITY
//    // hasImmunity
//    ofs << "set title \"hasImmunity\" font \"helvetica, 24\"" << std::endl
//        << "plot "<< HAS_IMMUNITY_OUTPUT << " w l"
//        << " title \"has_immunity_0\"" << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "replot " << HAS_IMMUNITY_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_immunity\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//#endif
//#ifdef OUTPUT_SIR
//    // SIR
//    ofs << "set title \"SIR\" font \"helvetica, 24\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"I\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"R\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//
//    // SIR_0
//    ofs << "set title \"SIR_0\" font \"helvetica, 24\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " w l"
//        << " title " << "\"R\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " w l"
//        << " title " << "\"I\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//    // SIR_RATIO
//    ofs << "set title \"SIR_RATIO\" font \"helvetica, 24\"" << std::endl;
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"I/POPULATION\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"R/POPULATION\"" << std::endl;
//    OFS_LINE ( "set autoscale y" );
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//    // SIR_0_RATIO
//    ofs << "set title \"SIR_0_RATIO\" font \"helvetica, 24\"" << std::endl;
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"I/POPULATION\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"R/POPULATION\"" << std::endl;
//    OFS_LINE ( "set autoscale y" );
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//#endif
//#ifdef OUTPUT_CONTACT
//    // contact
//    ofs << "set title \"infectioncontact\" font \"helvetica, 24\"" << std::endl
//        << "plot "<< CONTACT_OUTPUT << " w l"
//        << " title \"contact\"" << std::endl;
//    FOR( i, NUM_V ) {
//        ofs << "replot " << CONTACT_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"infection_contact_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//
//    ofs << "set title \"infectioncontactratio\" font \"helvetica, 24\"" << std::endl
//        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
//        << " title \"ratio\"" << std::endl;
//    ofs << "set output" << std::endl
//        << "pause -1" << std::endl;
//#endif
//}
//
///*
// *--------------------------------------------------------------------------------------
// *      Method:  Monitor :: generatePlotScriptForPng()
// * Description:  png出力用の自動化スクリプトを生成
// *--------------------------------------------------------------------------------------
// */
//void Monitor :: generatePlotScriptForPng() {
//    std::ofstream ofs(AUTO_GPLOT_FILENAME);
//    ofs << "set terminal png size "<< IMG_SIZE(1000, 200) << std::endl;
//    // population
//    scriptForPopulationPng(ofs);
//    // hasVirus
//    scriptForHasVirusPng(ofs);
//    // hasImmunity
//    scriptForHasImmunityPng(ofs);
//    // SIR
//    scriptForSIRPng(ofs);
//    // contact
//    scriptForContactPng(ofs);
//    ofs << "set output" << std::endl;
//}
//
///* 
// * ===  FUNCTION  ======================================================================
// *         Name:  scriptFor***png
// *  Description:  画像を出力するスクリプト
// * =====================================================================================
// */
//void Monitor :: scriptForPopulationPng(std::ofstream &ofs) {
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set output \"Population.png\"" << std::endl;
//    ofs << "set title \"Population\"" << std::endl;
//    ofs << "plot " << POPULATION_OUTPUT << " w l"
//        << " title " << "\"population\"" << std::endl;
//    // Mini size
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set output \"Population_mini.png\"" << std::endl;
//    ofs << "set title \"Population\"" << std::endl;
//    ofs << "plot " << POPULATION_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
//        << " title " << "\"population\"" << std::endl;
//    // Mini Last
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set output \"Population_last.png\"" << std::endl;
//    ofs << "set title \"Population\"" << std::endl;
//    ofs << "plot " << POPULATION_OUTPUT << EVERY_LAST(last_term_) << " w l"
//        << " title " << "\"population\"" << std::endl;
//}
//void Monitor :: scriptForHasVirusPng(std::ofstream &ofs) {
//    ofs << "set output \"HasVirus.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"HasVirus\"" << std::endl
//        << "plot " << HAS_VIRUS_OUTPUT << " w l"
//        << " title " << "\"has_virus_" << 0 << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasVirus.png\"" << std::endl;
//        ofs << "replot " << HAS_VIRUS_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_virus_" << i+1 << std::endl;
//    }
//    ofs << "set output \"HasVirus.png\"" << std::endl;
//    ofs << "replot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_virus\"" << std::endl;
//    // Mini size
//    ofs << "set output \"HasVirus_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"HasVirus\"" << std::endl
//        << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM <<" w l"
//        << " title " << "\"has_virus_" << 0 << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasVirus_mini.png\"" << std::endl;
//        ofs << "replot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_virus_" << i+1 << std::endl;
//    }
//    ofs << "set output \"HasVirus_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_virus\"" << std::endl;
//    // Mini Last
//    ofs << "set output \"HasVirus_last.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"HasVirus\"" << std::endl
//        << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_) <<" w l"
//        << " title " << "\"has_virus_" << 0 << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasVirus_last.png\"" << std::endl;
//        ofs << "replot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_virus_" << i+1 << std::endl;
//    }
//    ofs << "set output \"HasVirus_last.png\"" << std::endl;
//    ofs << "replot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_virus\"" << std::endl;
//}
//void Monitor :: scriptForHasImmunityPng(std::ofstream &ofs) {
//    OFS_OUTPUT( "HasImmunity.png" );
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"hasImmunity\"" << std::endl
//        << "plot "<< HAS_IMMUNITY_OUTPUT << " w l"
//        << " title \"has_immunity_0\"" << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasImmunity.png\"" << std::endl;
//        ofs << "replot " << HAS_IMMUNITY_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
//    }
//    OFS_OUTPUT( "HasImmunity.png" );
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_immunity\"" << std::endl;
//    // Mini Size
//    OFS_OUTPUT( "HasImmunity_mini.png" );
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"hasImmunity\"" << std::endl
//        << "plot "<< HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
//        << " title \"has_immunity_0\"" << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasImmunity_mini.png\"" << std::endl;
//        ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output \"HasImmunity_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_immunity\"" << std::endl;
//    // Mini Size
//    OFS_OUTPUT( "HasImmunity_last.png" );
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"hasImmunity\"" << std::endl
//        << "plot "<< HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_) <<" w l"
//        << " title \"has_immunity_0\"" << std::endl;
//    FOR( i, NUM_V-1 ) {
//        ofs << "set output \"HasImmunity_last.png\"" << std::endl;
//        ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output \"HasImmunity_last.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"has_all_immunity\"" << std::endl;
//}
//void Monitor :: scriptForSIRPng(std::ofstream &ofs) {
//    ofs << "set output \"SIR.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"I\"" << std::endl;
//    ofs << "set output \"SIR.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"R\"" << std::endl;
//
//    // SIR_0
//    ofs << "set output \"SIR_0.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR_0\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " w l"
//        << " title " << "\"I_0\"" << std::endl;
//    ofs << "set output \"SIR_0.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " w l"
//        << " title " << "\"R_0\"" << std::endl;
//    // SIR_RATIO
//    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"I/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"R/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // SIR_0_RATIO
//    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"I_0/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"R_0/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // Mini Size
//    ofs << "set output \"SIR_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"I\"" << std::endl;
//    ofs << "set output \"SIR_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"R\"" << std::endl;
//
//    // SIR_0
//    ofs << "set output \"SIR_0_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR_0\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
//        << " title " << "\"I_0\"" << std::endl;
//    ofs << "set output \"SIR_0_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<< " w l"
//        << " title " << "\"R_0\"" << std::endl;
//    // SIR_RATIO
//    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<< MINI_SIZE_TERM
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"I/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"R/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // SIR_0_RATIO
//    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::" << MINI_SIZE_TERM
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"I_0/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"R_0/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // Mini Last
//    ofs << "set output \"SIR_last.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"I\"" << std::endl;
//    ofs << "set output \"SIR_last.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+2 << " w l"
//        << " title " << "\"R\"" << std::endl;
//
//    // SIR_0
//    ofs << "set output \"SIR_0_last.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"SIR_0\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_) <<" w l"
//        << " title " << "\"I_0\"" << std::endl;
//    ofs << "set output \"SIR_0_last.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_) << " w l"
//        << " title " << "\"R_0\"" << std::endl;
//    // SIR_RATIO
//    ofs << "set output \"SIR_RATIO_last.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"I/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_RATIO_last.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+3 << " w l"
//        << " title " << "\"R/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // SIR_0_RATIO
//    ofs << "set output \"SIR_0_RATIO_last.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
//    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"I_0/POPULATION\"" << std::endl;
//    ofs << "set output \"SIR_0_RATIO_last.png\"" << std::endl;
//    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
//        << " using 1:" << NUM_V+4 << " w l"
//        << " title " << "\"R_0/POPULATION\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//}
//void Monitor :: scriptForContactPng(std::ofstream &ofs) {
//    ofs << "set output \"Contact.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"InfectionContact\"" << std::endl
//        << "plot "<< CONTACT_OUTPUT << " w l"
//        << " title \"contact\"" << std::endl;
//    FOR( i, NUM_V ) {
//        ofs << "set output \"Contact.png\"" << std::endl;
//        ofs << "replot " << CONTACT_OUTPUT
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output \"ContactRatio.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"InfectionContactRatio\"" << std::endl
//        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
//        << " title \"ratio\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // Mini Size
//    ofs << "set output \"Contact_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"InfectionContact\"" << std::endl
//        << "plot "<< CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
//        << " title \"contact\"" << std::endl;
//    FOR( i, NUM_V ) {
//        ofs << "set output \"Contact_mini.png\"" << std::endl;
//        ofs << "replot " << CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output \"ContactRatio_mini.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"InfectionContactRatio\"" << std::endl
//        << "plot " << CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" using 1:" << NUM_V+3 << " w l"
//        << " title \"ratio\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//    // Mini Last
//    ofs << "set output \"Contact_last.png\"" << std::endl;
//    OFS_LINE ( "set yl \"Agent\"" );
//    OFS_LINE ( "set xl \"Term\"" );
//    ofs << "set title \"InfectionContact\"" << std::endl
//        << "plot "<< CONTACT_OUTPUT << EVERY_LAST(last_term_) <<" w l"
//        << " title \"contact\"" << std::endl;
//    FOR( i, NUM_V ) {
//        ofs << "set output \"Contact_last.png\"" << std::endl;
//        ofs << "replot " << CONTACT_OUTPUT << EVERY_LAST(last_term_)
//            << " using 1:" << i+3 << " w l"
//            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
//    }
//    ofs << "set output \"ContactRatio_last.png\"" << std::endl;
//    OFS_LINE ( "set yl" );
//    OFS_LINE ( "set xl \"Term\"" );
//    OFS_LINE( "set yrange[0:1]" );
//    ofs << "set title \"InfectionContactRatio\"" << std::endl
//        << "plot " << CONTACT_OUTPUT << EVERY_LAST(last_term_) << " using 1:" << NUM_V+3 << " w l"
//        << " title \"ratio\"" << std::endl;
//    OFS_LINE( "set autoscale y" );
//}
//
///*
// *--------------------------------------------------------------------------------------
// *      Method:  Monitor :: generateResultHtml()
// * Description:  結果をまとめて表示させるHTMLファイルを出力する
// *--------------------------------------------------------------------------------------
// */
//void Monitor :: generateResultHtml( int t ) {
//    if( t < MINI_SIZE_TERM ) last_term_ = MINI_SIZE_TERM;
//    else last_term_ = t;
//    std::ofstream ofs( FNAME_RESULT_HTML );
//    OFS( "<html><link rel=\"stylesheet\" href=\"result.css\"><body><font color=gray><code>" );
//    OFS( "<h1><font color=black># 計算結果 "<<__DATE__<<", "<<__TIME__<<"</font></h1>" );
//    OFS( "<h2>設定</h2>" );
//    // table
//    OFS_LINE( "<table>" ); /* テーブル */
//#ifdef RANDOM_LOCATE                                                 /* 移動方法 */
//    OFS_TD( "[ 移動 ]", "土地にランダムに再配置される" );
//#else
//    OFS_TD( "[ 移動 ]", "エージェントが指定された距離を各々移動する" );
//#endif
//#ifdef AGING_AGENT                                                   /* 老化 */
//    OFS_TD( "[ 老化 ]", "する" );
//#else
//    OFS_TD( "[ 老化 ]", "しない" );
//#endif
//#ifdef MATING_AGENT                                                  /* 交配・出産 */
//    OFS_TD( "[ 交配 ]", "する" );
//#ifdef COUPLE_TAG                                                    /* 子供のタグ */
//    OFS_TD( "[ 子供のタグ ]", "親のタグ（カップルタグ）を元に初期化" );
//#else
//    OFS_TD( "[ 子供のタグ ]", "ランダムに初期化" );
//#endif
//#else
//    OFS_TD( "[ 交配 ]", "しない" );
//#endif
//    OFS_LINE( "</table>" );
//
//    OFS_LINE( "<br />" );
//
//    OFS_LINE( "<table>" ); /* テーブル */
//    OFS_LINE( "<tr>" );
//    OFS_LINE( "<th width=240px></th><th width=200px>タグ長</th><th width=200px>数</th>" );
//    OFS_LINE( "</tr>" );
//
//    OFS_LINE( "<tr>" );
//    OFS_LINE( "<td><font color=blue>ウイルス</td><td>"<<TAG_LEN_V<<"</td><td>"<<NUM_V<<"</td>" );
//    OFS_LINE( "</tr>" );
//    OFS_LINE( "<tr>" );
//    OFS_LINE( "<td><font color=red>エージェント</td><td>"<<TAG_LEN_A<<"</td><td>"<<INIT_NUM_A<<"</td>" );
//    OFS_LINE( "</tr>" );
//    OFS_LINE( "</table>" );
//
//    OFS_LINE( "<br />" );
//
//    OFS_LINE( "<table>" ); /* テーブル */
//    OFS_TD( "<font color=blue>ウイルスの感染確率</font>", INFECTION_RATE );
//    OFS_TD( "<font color=blue>１期間で感染させるウイルスの最大数</font>", MAX_V_AGENT_INFECT_ONT_TIME );
//    OFS_TD( "<font color=red>初期感染確率</font>", INIT_INFECTED_RATIO );
//#if defined(AGING_AGENT) || defined( MATING_AGENT)
//    OFS_TD( "<font color=red>エージェントの最大人数</font>", MAX_NUM_A );
//#endif
//#ifdef AGING_AGENT
//    OFS_TD( "<font color=red>寿命</font>", MAX_AGE );
//#endif
//#ifdef MATING_AGENT
//    OFS_TD( "<font color=red>出産確率</font>", BIRTH_RATE );
//#endif
//    OFS_TD( "土地の幅</font>", WIDTH );
//    OFS_TD( "最大実行期間</font>", TERM );
//#ifdef __unix__
//    OFS_TD( "実行期間</font>", Benchmark::Instance().getTime() );
//#endif
//    OFS_LINE( "</table>" );
//
//#if defined(AGING_AGENT) || defined( MATING_AGENT)
//    // 人口
//    OFS( "<h2>人口</h2>" );
//    OFS_IMG_MINI( "Population.png", "Population_mini.png", "Population_last.png" );
//    OFS( "</br>" );
//    OFS( "population: エージェントの総人口" );
//#endif
//    // 感染者
//    OFS( "<h2>感染者</h2>" );
//    OFS_IMG_MINI( "HasVirus.png", "HasVirus_mini.png", "HasVirus_last.png" );
//    FOR( i, NUM_V ) {
//        ofs << "<p>has_virus_" << i << ": "
//            << "ウイルス " << i << " に感染しているエージェント数</p>" << std::endl;
//    }
//    ofs << "<p>has_all_virus" << "すべてのウイルスに感染しているエージェント数</p>" << std::endl;
//    // 免疫獲得者
//    OFS( "<h2>免疫獲得者</h2>" );
//    OFS_IMG_MINI( "HasImmunity.png", "HasImmunity_mini.png", "HasImmunity_last.png" );
//    FOR( i, NUM_V ) {
//        ofs << "<p>has_virus_" << i << ": "
//            << "ウイルス " << i << " への免疫を獲得しているエージェント数</p>" << std::endl;
//    }
//    ofs << "<p>has_all_virus" << "すべてのウイルスへの免疫を獲得しているエージェント数</p>" << std::endl;
//    // SIR
//    OFS( "<h2>SIR</h2>" );
//    OFS_IMG_MINI( "SIR.png", "SIR_mini.png", "SIR_last.png" );
//    OFS( "I: すべてのウイルスに感染しているエージェント数" );
//    OFS( "R: すべてのウイルスに対して免疫を獲得しているエージェント数" );
//    OFS_IMG_MINI( "SIR_RATIO.png", "SIR_RATIO_mini.png", "SIR_RATIO_last.png" );
//    OFS( "I/POPULATION: すべてのウイルスに感染しているエージェント数 / その時点での総エージェント数" );
//    OFS( "R/POPULATION: すべてのウイルスに対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
//    OFS_IMG_MINI( "SIR_0.png", "SIR_0_mini.png", "SIR_0_last.png" );
//    OFS( "I: ウイルス 0 に感染しているエージェント数" );
//    OFS( "R: ウイルス 0 に対して免疫を獲得しているエージェント数" );
//    OFS_IMG_MINI( "SIR_0_RATIO.png", "SIR_0_RATIO_mini.png", "SIR_0_RATIO_last.png" );
//    OFS( "I/POPULATION: ウイルス 0 に感染しているエージェント数 / その時点での総エージェント数" );
//    OFS( "R/POPULATION: ウイルス 0 に対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
//    // 接触回数
//    OFS( "<h2>接触回数</h2>" );
//    OFS_IMG_MINI( "Contact.png", "Contact_mini.png", "Contact_last.png" );
//    OFS( "contact: 総接触回数" );
//    FOR( i, NUM_V ) {
//        ofs << "<p>infection_contact_" << i << ": "
//            << "ウイルス " << i << " を感染させた接触回数</p>" << std::endl;
//    }
//    OFS_IMG_MINI( "ContactRatio.png", "ContactRatio_mini.png", "ContactRatio_last.png" );
//    OFS( "ratio: 何らかのウイルスを感染させた接触回数 / 総接触回数" );
//    OFS( "</code></html></body>" );
//}

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

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: *
 * Description:  
 *--------------------------------------------------------------------------------------
 */

FileFactory& FileFactory :: Instance() {
    static FileFactory coredata;
    return coredata;                                                 /* インスタンスを返す */
}

void FileFactory :: setAdministrator( Administrator &admin ) {
    admin_ = &admin;                                                 /* 管理者を登録 */
}

void FileFactory :: generatePlotScript() {
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
    OFS_LINE( "set yrange[0:1]" );
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_LINE ( "set autoscale y" );
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
    // SIR_0_RATIO
    ofs << "set title \"SIR_0_RATIO\" font \"helvetica, 24\"" << std::endl;
    OFS_LINE( "set yrange[0:1]" );
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_LINE ( "set autoscale y" );
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
 *      Method:  FileFactory :: generatePlotScriptForPng()
 * Description:  png出力用の自動化スクリプトを生成
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: generatePlotScriptForPng() {
    std::ofstream ofs(AUTO_GPLOT_FILENAME);
    ofs << "set terminal png size "<< IMG_SIZE(1000, 200) << std::endl;
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
void FileFactory :: scriptForPopulationPng(std::ofstream &ofs) {
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set output \"Population.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl;
    ofs << "plot " << POPULATION_OUTPUT << " w l"
        << " title " << "\"population\"" << std::endl;
    // Mini size
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set output \"Population_mini.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl;
    ofs << "plot " << POPULATION_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title " << "\"population\"" << std::endl;
    // Mini Last
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set output \"Population_last.png\"" << std::endl;
    ofs << "set title \"Population\"" << std::endl;
    ofs << "plot " << POPULATION_OUTPUT << EVERY_LAST(last_term_) << " w l"
        << " title " << "\"population\"" << std::endl;
}
void FileFactory :: scriptForHasVirusPng(std::ofstream &ofs) {
    ofs << "set output \"HasVirus.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    // Mini Last
    ofs << "set output \"HasVirus_last.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"HasVirus\"" << std::endl
        << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_) <<" w l"
        << " title " << "\"has_virus_" << 0 << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasVirus_last.png\"" << std::endl;
        ofs << "replot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_virus_" << i+1 << std::endl;
    }
    ofs << "set output \"HasVirus_last.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_virus\"" << std::endl;
}
void FileFactory :: scriptForHasImmunityPng(std::ofstream &ofs) {
    OFS_OUTPUT( "HasImmunity.png" );
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    // Mini Size
    OFS_OUTPUT( "HasImmunity_last.png" );
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"hasImmunity\"" << std::endl
        << "plot "<< HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_) <<" w l"
        << " title \"has_immunity_0\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasImmunity_last.png\"" << std::endl;
        ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"HasImmunity_last.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
}
void FileFactory :: scriptForSIRPng(std::ofstream &ofs) {
    ofs << "set output \"SIR.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"SIR_0\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"I_0\"" << std::endl;
    ofs << "set output \"SIR_0.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " w l"
        << " title " << "\"R_0\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I_0/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R_0/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // Mini Size
    ofs << "set output \"SIR_mini.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"SIR_0\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" w l"
        << " title " << "\"I_0\"" << std::endl;
    ofs << "set output \"SIR_0_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<< " w l"
        << " title " << "\"R_0\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::"<< MINI_SIZE_TERM
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << " every ::0::" << MINI_SIZE_TERM
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I_0/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO_mini.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << " every ::0::"<<MINI_SIZE_TERM
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R_0/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // Mini Last
    ofs << "set output \"SIR_last.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"SIR\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output \"SIR_last.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"R\"" << std::endl;

    // SIR_0
    ofs << "set output \"SIR_0_last.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"SIR_0\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_) <<" w l"
        << " title " << "\"I_0\"" << std::endl;
    ofs << "set output \"SIR_0_last.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_) << " w l"
        << " title " << "\"R_0\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO_last.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO_last.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO_last.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"SIR_0_RATIO\"" << std::endl;
    ofs << "plot " << HAS_VIRUS_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I_0/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO_last.png\"" << std::endl;
    ofs << "replot " << HAS_IMMUNITY_OUTPUT << EVERY_LAST(last_term_)
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R_0/POPULATION\"" << std::endl;
    OFS_LINE( "set autoscale y" );
}
void FileFactory :: scriptForContactPng(std::ofstream &ofs) {
    ofs << "set output \"Contact.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"InfectionContactRatio\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // Mini Size
    ofs << "set output \"Contact_mini.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
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
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"InfectionContactRatio\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " every ::0::"<<MINI_SIZE_TERM<<" using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    OFS_LINE( "set autoscale y" );
    // Mini Last
    ofs << "set output \"Contact_last.png\"" << std::endl;
    OFS_LINE ( "set yl \"Agent\"" );
    OFS_LINE ( "set xl \"Term\"" );
    ofs << "set title \"InfectionContact\"" << std::endl
        << "plot "<< CONTACT_OUTPUT << EVERY_LAST(last_term_) <<" w l"
        << " title \"contact\"" << std::endl;
    FOR( i, NUM_V ) {
        ofs << "set output \"Contact_last.png\"" << std::endl;
        ofs << "replot " << CONTACT_OUTPUT << EVERY_LAST(last_term_)
            << " using 1:" << i+3 << " w l"
            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"ContactRatio_last.png\"" << std::endl;
    OFS_LINE ( "set yl" );
    OFS_LINE ( "set xl \"Term\"" );
    OFS_LINE( "set yrange[0:1]" );
    ofs << "set title \"InfectionContactRatio\"" << std::endl
        << "plot " << CONTACT_OUTPUT << EVERY_LAST(last_term_) << " using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
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
    OFS( "<html><link rel=\"stylesheet\" href=\"result.css\"><body><font color=gray><code>" );
    OFS( "<h1><font color=black># 計算結果 "<<__DATE__<<", "<<__TIME__<<"</font></h1>" );
    OFS( "<h2>設定</h2>" );
    // table
    OFS_LINE( "<table>" ); /* テーブル */
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

    OFS_LINE( "<table>" ); /* テーブル */
    OFS_LINE( "<tr>" );
    OFS_LINE( "<th width=240px></th><th width=200px>タグ長</th><th width=200px>数</th>" );
    OFS_LINE( "</tr>" );

    OFS_LINE( "<tr>" );
    OFS_LINE( "<td><font color=blue>ウイルス</td><td>"<<TAG_LEN_V<<"</td><td>"<<NUM_V<<"</td>" );
    OFS_LINE( "</tr>" );
    OFS_LINE( "<tr>" );
    OFS_LINE( "<td><font color=red>エージェント</td><td>"<<TAG_LEN_A<<"</td><td>"<<INIT_NUM_A<<"</td>" );
    OFS_LINE( "</tr>" );
    OFS_LINE( "</table>" );

    OFS_LINE( "<br />" );

    OFS_LINE( "<table>" ); /* テーブル */
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
#ifdef __unix__
    OFS_TD( "計算時間</font>", Benchmark::Instance().getTime() );
#endif
    OFS_LINE( "</table>" );

#if defined(AGING_AGENT) || defined( MATING_AGENT)
    // 人口
    OFS( "<h2>人口</h2>" );
    OFS_IMG_MINI( "Population.png", "Population_mini.png", "Population_last.png" );
    OFS( "</br>" );
    OFS( "population: エージェントの総人口" );
#endif
    // 感染者
    OFS( "<h2>感染者</h2>" );
    OFS_IMG_MINI( "HasVirus.png", "HasVirus_mini.png", "HasVirus_last.png" );
    FOR( i, NUM_V ) {
        ofs << "<p>has_virus_" << i << ": "
            << "ウイルス " << i << " に感染しているエージェント数</p>" << std::endl;
    }
    ofs << "<p>has_all_virus" << "すべてのウイルスに感染しているエージェント数</p>" << std::endl;
    // 免疫獲得者
    OFS( "<h2>免疫獲得者</h2>" );
    OFS_IMG_MINI( "HasImmunity.png", "HasImmunity_mini.png", "HasImmunity_last.png" );
    FOR( i, NUM_V ) {
        ofs << "<p>has_virus_" << i << ": "
            << "ウイルス " << i << " への免疫を獲得しているエージェント数</p>" << std::endl;
    }
    ofs << "<p>has_all_virus" << "すべてのウイルスへの免疫を獲得しているエージェント数</p>" << std::endl;
    // SIR
    OFS( "<h2>SIR</h2>" );
    OFS_IMG_MINI( "SIR.png", "SIR_mini.png", "SIR_last.png" );
    OFS( "I: すべてのウイルスに感染しているエージェント数" );
    OFS( "R: すべてのウイルスに対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_RATIO.png", "SIR_RATIO_mini.png", "SIR_RATIO_last.png" );
    OFS( "I/POPULATION: すべてのウイルスに感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: すべてのウイルスに対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    OFS_IMG_MINI( "SIR_0.png", "SIR_0_mini.png", "SIR_0_last.png" );
    OFS( "I: ウイルス 0 に感染しているエージェント数" );
    OFS( "R: ウイルス 0 に対して免疫を獲得しているエージェント数" );
    OFS_IMG_MINI( "SIR_0_RATIO.png", "SIR_0_RATIO_mini.png", "SIR_0_RATIO_last.png" );
    OFS( "I/POPULATION: ウイルス 0 に感染しているエージェント数 / その時点での総エージェント数" );
    OFS( "R/POPULATION: ウイルス 0 に対して免疫を獲得しているエージェント数 / その時点での総エージェント数" );
    // 接触回数
    OFS( "<h2>接触回数</h2>" );
    OFS_IMG_MINI( "Contact.png", "Contact_mini.png", "Contact_last.png" );
    OFS( "contact: 総接触回数" );
    FOR( i, NUM_V ) {
        ofs << "<p>infection_contact_" << i << ": "
            << "ウイルス " << i << " を感染させた接触回数</p>" << std::endl;
    }
    OFS_IMG_MINI( "ContactRatio.png", "ContactRatio_mini.png", "ContactRatio_last.png" );
    OFS( "ratio: 何らかのウイルスを感染させた接触回数 / 総接触回数" );
    OFS( "</code></html></body>" );
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_HasVirus
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_HasVirus( const char *fname ) {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* ファイルに出力 */
    FOR( j, NUM_V ) {
        ofs << admin_->numHasVirus( admin_->virus_[j] ) << SEPARATOR;                /* ウイルス j の保持者 */
    }
    int num_has_all = admin_->numHasAllVirus();
    ofs << num_has_all << SEPARATOR;                                 /* 全ウイルス保持者 */
    ofs << (double)num_has_all/admin_->agent_.size() << SEPARATOR;
    ofs << (double)admin_->numHasVirus(admin_->virus_[0])/admin_->agent_.size() << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_HasImmunity
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_HasImmunity( const char *fname ) {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                           /* ファイルに出力 */
    FOR( k, NUM_V ) {
        ofs << admin_->numHasImmunity( admin_->virus_[k] ) << SEPARATOR;             /* ウイルスに対する免疫獲得者数 */
    }
    int num_has_all = admin_->numHasAllImmunity();
    ofs << num_has_all << SEPARATOR;
    ofs << (double)num_has_all/admin_->agent_.size() << SEPARATOR;
    ofs << (double)admin_->numHasImmunity( admin_->virus_[0] )/admin_->agent_.size() << std::endl;
}
/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_Population
 * Description:  人口推移を出力する
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_Population( const char *fname ) {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    ofs << admin_->getTerm() << SEPARATOR;                                   /* 期間 */
    ofs << admin_->agent_.size() << SEPARATOR;                               /* 人口 */
    ofs << std::endl;
}

/*--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_InfectionContactRatio
 * Description:  ファイルに出力する
 *               ウイルスの数によって、列を調整できる
 *----------------------------------------------------------------------------------- */
void FileFactory :: outputFile_InfectionContactRatio( const char *fname ) {
    if( admin_->getTerm() % OUTPUT_INTERVAL != 0 ) return;
    static std::ofstream ofs(fname);                                 /* インスタンスは１つだけ */
    double ratio = 0;
    int sum = 0;                                                     /* 何らかのウイルスに感染した接触回数 */

    ofs << admin_->getTerm() << SEPARATOR;                                   /* 期間 */
    ofs << Monitor::Instance().getContactNum() << SEPARATOR;         /* 総接触数 */
    FOR( j, NUM_V ) {                                                /* その内感染した回数 */
        sum += Monitor::Instance().getInfectionContactNum(&admin_->virus_[j]);
        ofs << Monitor::Instance().getInfectionContactNum(&admin_->virus_[j]) << SEPARATOR;
    }

    if( sum > 0 ) ratio
        = (double)sum / (double) Monitor::Instance().getContactNum(); 
    ofs << ratio << std::endl;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  FileFactory :: outputFile_LastLog( const char * )
 * Description:  最終、初期状態を出力
 *--------------------------------------------------------------------------------------
 */
void FileFactory :: outputFile_LastLog( const char *fname ) {
    static std::ofstream ofs(fname);
    ofs << "TERM:" << admin_->getTerm() << std::endl;
    ofs << "MAX_AGE:" << MAX_AGE << std::endl;
    ofs << "BIRTH_RATE:" << BIRTH_RATE << std::endl;
    ofs << "WIDTH:" << WIDTH << std::endl;
    ofs << "NUM_A:" << admin_->agent_.size() << std::endl;
    ofs << "INIT_NUM_A:" << INIT_NUM_A << std::endl;
    ofs << "NUM_V:" << NUM_V << std::endl;
    ofs << "INFECTION_RATE:" << INFECTION_RATE << std::endl;
    ofs << "INIT_INFECTED_RATIO:" << INIT_INFECTED_RATIO << std::endl;
    ofs << "TAG_LEN_A:" << TAG_LEN_A << std::endl;
    ofs << "TAG_LEN_V:" << TAG_LEN_V << std::endl;
    FOR(i,NUM_V) { ofs<<"["<<admin_->virus_[i].getLen()<<"]:";
        FOR(j, admin_->virus_[i].getLen()) { ofs<<int(admin_->virus_[i].tagAt(j)); } ofs<<std::endl; }
    ofs << ">>> Agent Last Status" << std::endl;
    ITERATOR(Agent *) it_a = admin_->agent_.begin();
    while(it_a!=admin_->agent_.end()) {
        FOR(j, (*it_a)->getLen()) {
            ofs<<(*it_a)->tagAt(j);                                  /* エージェントのタグ */
        }
        ofs<<" "<<(*it_a)->numHoldingVirus();                        /* エージェントの保持ウイルス数 */
        ofs<<std::endl;
        it_a++;
    }
}
