/*
 * =====================================================================================
 *
 *       Filename:  Monitor.cpp
 *
 *    Description:  
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

#define GPLOT_FILENAME      "plot2.gpi"
#define HAS_VIRUS_OUTPUT     "\"A_hasVirus.txt\""
#define HAS_IMMUNITY_OUTPUT     "\"A_hasImmunity.txt\""
#define CONTACT_OUTPUT     "\"A_infectionContact.txt\""
#define POPULATION_OUTPUT     "\"A_Population.txt\""

Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: *
 * Description:  
 *--------------------------------------------------------------------------------------
 */
int Monitor :: getContactNum() const { return num_contact_; }
int Monitor :: getInfectionContactNum( __TagInterface *t ) { return num_infection_contact_[ t ]; }

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: resetAll()
 * Description:  
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
        << " title " << "\"population" << std::endl;
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
