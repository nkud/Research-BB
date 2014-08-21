#ifndef ___AGENT_HPP
#define ___AGENT_HPP

#include "Gene.hpp"
#include "Mobile.hpp"
#include "Function.hpp"
#include "Landscape.hpp"

class Virus;
class ImmuneSystem;

/**
 * @brief ヒト
 */
class Human : public Gene, public __Mobile
{
  public:
    Human();

    bool infection();                            // 観戦する
    void contact();                              // 接触する

    void reborn();                               // 初期化される
    ImmuneSystem& getImmuneSystem();
  private:
    ImmuneSystem *immune_system_;                // 免疫機構
};

class HumanLand : public __Landscape
{
  public:
    VECTOR(Human *)& getHumanListAt( int x, int y );
    VECTOR(Human *) getNeighborsAt( Human& human );
    VECTOR(Human *) getHumanList();
    int getHumanListSize();

    HumanLand( int width, int height );
    ~HumanLand();
  private:
    VECTOR(Human *) *human_list_;
};

#endif
