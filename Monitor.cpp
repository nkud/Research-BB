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

#define GPLOT_FILENAME      "plot2.gpi"
#define OUTPUT_FILENAME     "\"A_hasVirus.dat\""

Monitor& Monitor :: Instance() {
    static Monitor coredata;
    return coredata;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: resetAll()
 * Description:  
 *--------------------------------------------------------------------------------------
 */
void Monitor :: resetAll() {
    num_infection_contact_ = 0;
    num_contact_ = 0;
    num_has_immunity_all_virus_ = 0;
    num_infect_others = 0;
}

void Monitor :: countUpInfectionContact() {
    num_infection_contact_++;
}
void Monitor :: countUpContact() {
    num_contact_++;
}
void Monitor :: countUpHasImmunityAllVirus() {
    num_has_immunity_all_virus_++;
}
void Monitor :: countUpInfectOthers() {
    num_infect_others++;
}

/*
 *--------------------------------------------------------------------------------------
 *      Method:  Monitor :: generatePlotScript()
 * Description:  プロット用のスクリプトを生成
 *--------------------------------------------------------------------------------------
 */
void Monitor :: generatePlotScript() {
    std::ofstream ofs(GPLOT_FILENAME);
    ofs << "set title \"ウイルス保持者\" font \"helvetica, 24\"" << std::endl
        << "plot " << OUTPUT_FILENAME << " w l"
        << " title " << "\"ウイルス" << 0 << "保持\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "replot " << OUTPUT_FILENAME
            << " using 1:" << i+3 << " w l"
            << " title " << "\"ウイルス" << i+1 << "保持\"" << std::endl;
    }
    ofs << "replot " << OUTPUT_FILENAME
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"全ウイルス保持\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;

    ofs << "set title \"infectioncontact\" font \"helvetica, 24\"" << std::endl
        << "plot \"A_infectionContact.dat\" w l title \"ratio\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
}
