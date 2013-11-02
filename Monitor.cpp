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
#define HAS_VIRUS_OUTPUT     "\"A_hasVirus.txt\""
#define HAS_IMMUNITY_OUTPUT     "\"A_hasImmunity.txt\""
#define CONTACT_OUTPUT     "\"A_infectionContact.txt\""

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
    num_contact_ = 0;
    num_has_immunity_all_virus_ = 0;
    num_infect_others = 0;
    num_infection_contact_.clear();
}

void Monitor :: countUpInfectionContact(__TagInterface *pv) {
    num_infection_contact_[pv]++;
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

    // hasVirus
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

    // hasImmunity
    ofs << "set title \"hasImmunity\" font \"helvetica, 24\"" << std::endl
        << "plot "<< HAS_IMMUNITY_OUTPUT << " w l"
        << " title \"has_immunity_0\"" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "replot " << HAS_IMMUNITY_OUTPUT
            << " using 1:" << i+3 << " w l"
            << " title " << "\"has_immunity_" << i+1 << "\"" << std::endl;
    }
    ofs << "replot " << HAS_VIRUS_OUTPUT
        << " using 1:" << NUM_V+2 << " w l"
        << " title " << "\"has_all_immunity\"" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;

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
}
