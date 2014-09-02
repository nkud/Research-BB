#ifndef ___AGENT_HPP
#define ___AGENT_HPP

#include "Gene.hpp"
#include "Mobile.hpp"
#include "Function.hpp"
#include "Landscape.hpp"
#include "Host.hpp"

class Virus;
class CellLand;
class Tcell;

/**
 * @brief ヒト
 */
class Human : public __Mobile
{
  public:
    Human( int tlen, int tsize, CellLand *land );

    void reborn();                               ///< 初期化される

    void contact( Human& neighbor );            ///< ホストと接触
    bool infection();                            ///< 待機ウイルスを感染させる

    // 宿主内状態
    bool isSusceptible();                        ///< 未感染者
    bool isIncubationPeriod();                   ///< 潜伏期間
    bool isSymptomaticPeriod();                  ///< 症候性期間

    VECTOR(Virus *)& getStandByVirusList() { return stand_by_virus_list_; } // 待機ウイルスリストを取得
    void pushVirusToStandByVirusList( Virus& v ); // 待機ウイルスに追加

    void clearStandByViruses();
    VECTOR(Virus *)& getInfectedVirusList();

    //----------------------------------------------------------------------
    //  宿主内用関数
    //----------------------------------------------------------------------
    CellLand& getCellLand() { return *cell_land_; }
    VECTOR(Tcell *)& getTcellList() { return tcell_list_; }
    int getTcellListSize() const { return tcell_list_.size(); } ///< T細胞数を取得する

    bool enoughNumberOfTcellToRemove( int min_tcell ); ///< T細胞が十分数あるか評価する
    ITERATOR(Tcell *) eraseTcell( ITERATOR(Tcell *)& it_tcell ); ///< T細胞を削除する

  private:
    CellLand *cell_land_;                        ///< 細胞土地
    VECTOR(Tcell *) tcell_list_;                 ///< T細胞リスト

    VECTOR(Virus *) stand_by_virus_list_;        ///< 待機ウイルスリスト
    VECTOR(Virus *) infected_virus_list_;        ///< 待機ウイルスリスト
};

/**
 * @brief ヒトの土地
 */
class HumanLand : public __Landscape
{
  public:
    VECTOR(Human *)& getHumanListAt( int x, int y ); ///< ヒトを取得する
    VECTOR(Human *) getNeighborsAt( Human& human ); ///< 近隣を取得する
    VECTOR(Human *)& getHumanList() { return *human_list_; } ///< ヒト配列を取得する

    void clearMap();                             ///< 土地の登録をクリア
    void resistHuman( Human& human );            ///< 土地にヒトを登録する

    HumanLand( int width, int height );
    ~HumanLand();
  private:
    VECTOR(Human *) *human_list_;
};

#endif
