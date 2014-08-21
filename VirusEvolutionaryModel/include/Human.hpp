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

    void move();

    bool infection( Virus& v );

    void reborn();                // 初期化される
    ImmuneSystem& getImmuneSystem();
  private:
    ImmuneSystem *immune_system_;
};

class HumanLand : public __Landscape
{
  public:
//    VECTOR(Human *)& getHumanAt( int x, int y );
    VECTOR(Human *)& getHumanAt( Human& human );
    const VECTOR(Human *) getNeighborsAt( int x, int y ) const;
    VECTOR(Human *) getHumanList();
    int getHumanListSize();

    HumanLand( int width, int height );
    ~HumanLand();
  private:
    VECTOR(Human *) *human_list_;
};

#endif
