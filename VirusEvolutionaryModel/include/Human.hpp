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
    void contact( VECTOR(Human *)& neighbors );  // 接触する

    void reborn();                               // 初期化される
    ImmuneSystem& getImmuneSystem();

    VECTOR(Virus *)& getStandByVirusList() { return stand_by_virus_list_; }
    void pushCloneToStandByVirusList( Virus& virus );
    VECTOR(Virus *) getInfectedVirusList();     // XXX
  private:
    VECTOR(Virus *) stand_by_virus_list_;
    ImmuneSystem *immune_system_;                // 免疫機構
};

class HumanLand : public __Landscape
{
  public:
    VECTOR(Human *)& getHumanListAt( int x, int y );
    VECTOR(Human *) getNeighborsAt( Human& human );
    VECTOR(Human *)& getHumanList() { return *human_list_; }

    void clearMap();                             // 土地の登録をクリア
    void resistHuman( Human& human );            // 土地にヒトを登録する

    HumanLand( int width, int height );
    ~HumanLand();
  private:
    VECTOR(Human *) *human_list_;
};

#endif
