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

#define GPLOT_FILENAME          "plot2.gpi"
#define AUTO_GPLOT_FILENAME     "auto.plt"
#define HAS_VIRUS_OUTPUT        "\"A_hasVirus.txt\""
#define HAS_IMMUNITY_OUTPUT     "\"A_hasImmunity.txt\""
#define CONTACT_OUTPUT          "\"A_infectionContact.txt\""
#define POPULATION_OUTPUT       "\"A_population.txt\""

Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: *
 * Description:  ゲッタ
 *--------------------------------------------------------------------------------------
 */
int Monitor :: getContactNum() const { return num_contact_; }
int Monitor :: getInfectionContactNum( __TagInterface *t ) { return num_infection_contact_[ t ]; }

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
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+1 << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+1 << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;

    // SIR_0
    ofs << "set title \"SIR_0\" font \"helvetica, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"I\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
    // SIR_RATIO
    ofs << "set title \"SIR_RATIO\" font \"helvetica, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
    // SIR_0_RATIO
    ofs << "set title \"SIR_0_RATIO\" font \"helvetica, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
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
            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
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
    ofs << "set output \"Population.png\"" << std::endl;
    ofs << "set title \"Population\" font \"monospace, 24\"" << std::endl
        << "plot " << POPULATION_OUTPUT << " w l"
        << " title " << "\"population\"" << std::endl;
    ofs << "set output \"HasVirus.png\"" << std::endl;
    ofs << "set title \"ウイルス保持者\" font \"monospace, 24\"" << std::endl
        << "plot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"ウイルス" << 0 << "保持\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "set output \"HasVirus.png\"" << std::endl;
        ofs << "replot " << HAS_VIRUS_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"ウイルス" << i+1 << "保持\"" << std::endl;
    }
    ofs << "set output \"HasVirus.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"全ウイルス保持\"" << std::endl;
    // hasImmunity
    ofs << "set output \"HasImmunity.png\"" << std::endl;
    ofs << "set title \"hasImmunity\" font \"monospace, 24\"" << std::endl
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
    ofs << "set title \"SIR\" font \"monospace, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+1 << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "set output \"SIR.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+1 << " w l"
        << " title " << "\"I\"" << std::endl;

    // SIR_0
    ofs << "set output \"SIR_0.png\"" << std::endl;
    ofs << "set title \"SIR_0\" font \"monospace, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT << " w l"
        << " title " << "\"R\"" << std::endl;
    ofs << "set output \"SIR_0.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT << " w l"
        << " title " << "\"I\"" << std::endl;
    // SIR_RATIO
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    ofs << "set title \"SIR_RATIO\" font \"monospace, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+3 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    // SIR_0_RATIO
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    ofs << "set title \"SIR_0_RATIO\" font \"monospace, 24\"" << std::endl;
    ofs << "plot " << HAS_IMMUNITY_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"R/POPULATION\"" << std::endl;
    ofs << "set output \"SIR_0_RATIO.png\"" << std::endl;
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+4 << " w l"
        << " title " << "\"I/POPULATION\"" << std::endl;
    // contact
    ofs << "set output \"Contact.png\"" << std::endl;
    ofs << "set title \"InfectionContact\" font \"monospace, 24\"" << std::endl
        << "plot "<< CONTACT_OUTPUT << " w l"
        << " title \"contact\"" << std::endl;
    FOR( i, NUM_V ) {
        ofs << "set output \"Contact.png\"" << std::endl;
        ofs << "replot " << CONTACT_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"infect_contact_" << i+1 << "\"" << std::endl;
    }
    ofs << "set output \"ContactRatio.png\"" << std::endl;
    ofs << "set title \"InfectionContactRatio\" font \"monospace, 24\"" << std::endl
        << "plot " << CONTACT_OUTPUT << " using 1:" << NUM_V+3 << " w l"
        << " title \"ratio\"" << std::endl;
    ofs << "output" << std::endl;
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
