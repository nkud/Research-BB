#ifndef ___VIRUS_HPP
#define ___VIRUS_HPP

#include "Gene.hpp"

/**
 * @brief ウイルス
 */
class Virus : public __Life
{
 public:
  int getInfectionRate();                        /// 感染確率
  int getMutationRate();                         /// 突然変異確率
  Virus& clone();                                /// クローンを作成する
 private:
};

#endif
