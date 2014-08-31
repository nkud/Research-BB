#ifndef ___HOST_HPP
#define ___HOST_HPP

#include "Function.hpp"

class Virus;

/**
 * @brief 宿主
 *
 * 遺伝子を持つとは限らない
 */
class __Host
{
  public:
    __Host() : max_virus_can_have_(1) { }
    ~__Host() { }

    virtual void clearInfectedViruses();         // 感染ウイルスをクリア
    virtual void clearStandByViruses();          // 待機ウイルスをクリア

    virtual VECTOR(Virus *)& getInfectedVirusList(); // 感染ウイルスリストを取得
    virtual VECTOR(Virus *)& getStandByVirusList(); // 待機ウイルスリストを取得

    virtual void pushVirusToStandByVirusList( Virus& v ); // 待機ウイルスに追加
    virtual void pushNewVirusCloneToInfectedVirusList( Virus& v ); // クローンを感染ウイルスに追加
    virtual bool canPushNewVirus();              // 新しいウイルスを追加できるか評価

    virtual void contact( __Host& neighbors ) = 0; // ホストと接触
    virtual bool infection() = 0;                // 待機ウイルスを感染させる
    
    virtual int getInfectedVirusListSize() const { return infected_virus_list_.size(); }

  private:
    int max_virus_can_have_;                     // 最大感染ウイルス数
    VECTOR(Virus *) infected_virus_list_;        // 感染ウイルスリスト
    VECTOR(Virus *) stand_by_virus_list_;        // 待機ウイルスリスト
};

#endif
