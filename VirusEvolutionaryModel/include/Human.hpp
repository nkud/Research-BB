#ifndef ___AGENT_HPP
#define ___AGENT_HPP

#include "Gene.hpp"
#include "Mobile.hpp"
#include "Function.hpp"
#include "Landscape.hpp"
#include "Host.hpp"

class Virus;
class ImmuneSystem;

/**
 * @brief ヒト
 */
class Human : public __Life, public __Mobile, public __Host
{
  public:
    Human();

    bool infection();                            // 観戦する
    void contact( VECTOR(Human *)& neighbors );  // 接触する

    void reborn();                               // 初期化される
    ImmuneSystem& getImmuneSystem();

  private:
    ImmuneSystem *immune_system_;                // 免疫機構
};

/**
 * @brief ヒトの土地
 */
class HumanLand : public __Landscape
{
  public:
    VECTOR(Human *)& getHumanListAt( int x, int y ); // ヒトを取得する
    VECTOR(Human *) getNeighborsAt( Human& human ); // 近隣を取得する
    VECTOR(Human *)& getHumanList() { return *human_list_; } // ヒト配列を取得する

    void clearMap();                             // 土地の登録をクリア
    void resistHuman( Human& human );            // 土地にヒトを登録する

    HumanLand( int width, int height );
    ~HumanLand();
  private:
    VECTOR(Human *) *human_list_;
};

#endif
