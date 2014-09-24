#ifndef ___CELL_HPP
#define ___CELL_HPP

#include "Function.hpp"
#include "Landscape.hpp"
#include "Mobile.hpp"
#include "Host.hpp"
#include "Gene.hpp"

class Virus;

/// 細胞
class Cell : public __Location, public __Life
{
  public:
    Cell( int x, int y, int clen);
    bool isInfected();                           ///< 感染の真偽
    bool isNotInfected();                        ///< 未感染の真偽

    // ホスト関数
    void clearInfectedViruses();                 ///< 感染ウイルスをクリア
    void clearStandByViruses();                  ///< 待機ウイルスをクリア

    VECTOR(Virus *)& getInfectedVirusList();     ///< 感染ウイルスリストを取得
    VECTOR(Virus *)& getStandByVirusList();      ///< 待機ウイルスリストを取得

    void pushVirusToStandByVirusList( Virus& v ); ///< 待機ウイルスに追加
    void pushNewVirusCloneToInfectedVirusList( Virus& v ); // クローンを感染ウイルスに追加
    bool canPushNewVirus();                      ///< 新しいウイルスを追加できるか評価

    void contact( Cell& neighbors );             ///< ホストと接触
    bool infection();                            ///< 待機ウイルスを感染させる

    int getInfectedVirusListSize() const { return infected_virus_list_.size(); }

    double calcDensityOfVirusSize() const;       ///< 細胞の最大保持ウイルス数に対する現ウイルス密度を計算
    int getMaxSizeOfInfectedVirus() const { return max_virus_can_have_; }

  private:
    int max_virus_can_have_;                     ///< 最大感染ウイルス数
    VECTOR(Virus *) infected_virus_list_;        ///< 感染ウイルスリスト
    VECTOR(Virus *) stand_by_virus_list_;        ///< 待機ウイルスリスト
};

/**
 * @brief 細胞土地
 */
class CellLand : public __Landscape
{
  public:
    CellLand( int width, int height, int clen );
    Cell& getCellAt( int x, int y );
    VECTOR(Cell *) getNeighborsAt( Cell& cell ); ///< 近隣を取得する
    VECTOR(Cell *)& getCellList() { return cell_list_; }
    int getCellListSize() const;                 ///< 細胞数を取得する

    double calcDensityOfInfectedVirus();            ///< 感染細胞の密度を計算する
    int countInfectedCell();                     ///< 感染細胞の数を数える
  private:
    CellLand();
    VECTOR(Cell *) cell_list_;
};

#endif
