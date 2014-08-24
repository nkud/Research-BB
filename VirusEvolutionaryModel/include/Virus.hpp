#ifndef ___VIRUS_HPP
#define ___VIRUS_HPP

#include "Gene.hpp"

/**
 * @brief ウイルス
 *
 * 遺伝子を持つ
 */
class Virus : public Gene
{
 public:
   Virus( const char *tag ) : Gene( tag ) { }
   Virus( int len ) : Gene( len ) { }

  int getInfectionRate();                        ///< 感染確率
  int getMutationRate();                         ///< 突然変異確率

  Virus *clone();                                ///< クローンを作成する
 private:
};

#endif
