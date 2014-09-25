#ifndef ___VIRUS_HPP
#define ___VIRUS_HPP

#include "Gene.hpp"

#include <string>

class Cell;

/**
 * @brief ウイルス
 *
 * 遺伝子を持つ
 */
class Virus : public Gene
{
 public:
   Virus( const char *tag ) : Gene( tag ) { }
   Virus( std::string& tag ) : Gene( tag ) { }
   Virus( int len ) : Gene( len ) { }

  int getInfectionRate();                        ///< 感染確率
  int getInfectionRate( Cell& cell);             ///< 感染確率
  int getMutationRate();                         ///< 突然変異確率
  //  int getReproductiveRate() const; // 増殖率

  int getAdaptationRateForCell( Cell& cell ); // 細胞の受容体に対する適合度

  Virus *clone();                                ///< クローンを作成する
 private:
};

#endif
