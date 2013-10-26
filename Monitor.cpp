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

Monitor& Monitor :: getInstance() {
    static Monitor coredata;
    return coredata;
}

void Monitor :: resetAll() {
    count_infection_contact_ = 0;
}

void Monitor :: generatePlotScript() {
    std::ofstream ofs(GPLOT_FILENAME);
    ofs << "set title \"hasVirus\" font \"helvetica, 24\"" << std::endl
        << "plot " << OUTPUT_FILENAME << " w l" << std::endl;
    FOR( i, NUM_V-1 ) {
        ofs << "replot " << OUTPUT_FILENAME << " using 1:" << i+3 << " w l" << std::endl;
    }
    ofs << "replot " << OUTPUT_FILENAME << " using 1:" << NUM_V+2 << " w l" << std::endl;
    ofs << "set output" << std::endl
        << "pause -1" << std::endl;
}
