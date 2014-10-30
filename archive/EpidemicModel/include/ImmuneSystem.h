#ifndef ___IMMUNESYSTEM
#define ___IMMUNESYSTEM

#include "Function.h"

class Agent;
class __VirusInterface;

class ImmuneSystem {
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    ImmuneSystem();
    virtual ~ImmuneSystem();
    /*-----------------------------------------------------------------------------
     *  免疫機構操作
     *-----------------------------------------------------------------------------*/
    bool infection( Agent &self, __VirusInterface &v );                         /* 感染プロセス  */
    int response( Agent &self );                                     /* 免疫応答する（タグフリップ）  */

    int progressDisease();

    bool hasVirus( __VirusInterface & );
    bool hasVirus() const;
    void incrementInfectionTime();
    int getInfectionTime() const;
    void resetInfectionTime();

    bool isSusceptible();
    bool isIncubationPeriod();
    bool isSymptomaticPeriod();
    bool isLethal();
    /*-----------------------------------------------------------------------------
     *  保持ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    __VirusInterface *getVirusAt( int ) const;                                  /* 指定の保持ウイルスを返す */
//    __VirusInterface *getOnSetVirusAt( int );
    int getVirusListSize() const;                                    /* 保持ウイルスのリストを返す */
//    int getOnSetVirusListSize();
    void pushVirus( __VirusInterface& virus, Agent& agent );                                       /* 保持ウイルスに追加する */
    ITERATOR(__VirusInterface *) eraseVirus( std::vector<__VirusInterface *>::iterator );               /* 指定の保持ウイルスを削除する */
    bool hasNoVirus() const;                                         /* ウイルスを保持していない */
    std::vector<__VirusInterface *>::iterator getVirusListIteratorBegin();      /* 先頭へのイテレータを返す */
    std::vector<__VirusInterface *>::iterator getVirusListIteratorEnd();        /* 末尾へのイテレータを返す */
    VECTOR(__VirusInterface *)& getVirusList() { return virus_list_; }

    VECTOR(__VirusInterface *) getCrisisVirusList();
    /*-----------------------------------------------------------------------------
     *  待機ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    __VirusInterface *getStandByVirusAt( int n ) const;                         /* 指定の待機ウイルスを返す */
    void pushStandByVirus( __VirusInterface& v );                               /* 待機ウイルスに追加する */
    int getStandByVirusListSize() const;                             /* 待機ウイルスの数を返す */
    bool hasNoStandByVirus() const;                                  /* ウイルスを保持していない */
    std::vector<__VirusInterface *>::iterator getStandByVirusListIteratorBegin(); /* 先頭へのイテレータを返す */
    std::vector<__VirusInterface *>::iterator getStandByVirusListIteratorEnd(); /* 末尾へのイテレータを返す */
    ITERATOR(__VirusInterface *) eraseStandByVirus( std::vector<__VirusInterface *>::iterator it );     /* 指定の待機ウイルスを削除 */
    void clearStandByVirus();                                        /* 待機ウイルスをすべて削除 */
    VECTOR(__VirusInterface *)& getStandByVirusList() { return stand_by_virus_list_; }
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    int infection_time_;                                             /* 感染期間 */
    /*-----------------------------------------------------------------------------
     *  配列
     *-----------------------------------------------------------------------------*/
    VECTOR(__VirusInterface *) virus_list_;                               /* 保持ウイルスのリスト */
    VECTOR(__VirusInterface *) stand_by_virus_list_;                      /* 待機ウイルスリスト */
};

#endif
