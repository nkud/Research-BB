#ifndef ___VIRUS_HPP
#define ___VIRUS_HPP

#include "Gene.hpp"

/**
 * @brief ウイルス
 */
class Virus : public Gene
{
 public:
  int getInfectionRate();
  int getMutationRate();
  Virus& clone();  // クローンを作成する
 private:
};

#endif
