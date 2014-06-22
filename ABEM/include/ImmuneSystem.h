#ifndef ___IMMUNESYSTEM
#define ___IMMUNESYSTEM

class Agent;

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
    bool infection( Agent &self, Virus &v );                         /* 感染プロセス  */
    int response( Agent &self );                                     /* 免疫応答する（タグフリップ）  */

    int progressDisease();

    bool hasVirus( Virus & );
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
    Virus *getVirusAt( int ) const;                                  /* 指定の保持ウイルスを返す */
//    Virus *getOnSetVirusAt( int );
    int getVirusListSize() const;                                    /* 保持ウイルスのリストを返す */
//    int getOnSetVirusListSize();
    void pushVirus( Virus& virus, Agent& agent );                                       /* 保持ウイルスに追加する */
    ITERATOR(Virus *) eraseVirus( std::vector<Virus *>::iterator );               /* 指定の保持ウイルスを削除する */
    bool hasNoVirus() const;                                         /* ウイルスを保持していない */
    std::vector<Virus *>::iterator getVirusListIteratorBegin();      /* 先頭へのイテレータを返す */
    std::vector<Virus *>::iterator getVirusListIteratorEnd();        /* 末尾へのイテレータを返す */
    VECTOR(Virus *)& getVirusList() { return virus_list_; }

    VECTOR(Virus *) getCrisisVirusList();
    /*-----------------------------------------------------------------------------
     *  待機ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    Virus *getStandByVirusAt( int n ) const;                         /* 指定の待機ウイルスを返す */
    void pushStandByVirus( Virus& v );                               /* 待機ウイルスに追加する */
    int getStandByVirusListSize() const;                             /* 待機ウイルスの数を返す */
    bool hasNoStandByVirus() const;                                  /* ウイルスを保持していない */
    std::vector<Virus *>::iterator getStandByVirusListIteratorBegin(); /* 先頭へのイテレータを返す */
    std::vector<Virus *>::iterator getStandByVirusListIteratorEnd(); /* 末尾へのイテレータを返す */
    ITERATOR(Virus *) eraseStandByVirus( std::vector<Virus *>::iterator it );     /* 指定の待機ウイルスを削除 */
    void clearStandByVirus();                                        /* 待機ウイルスをすべて削除 */
    VECTOR(Virus *)& getStandByVirusList() { return stand_by_virus_list_; }
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    int infection_time_;                                             /* 感染期間 */
    /*-----------------------------------------------------------------------------
     *  配列
     *-----------------------------------------------------------------------------*/
    VECTOR(Virus *) virus_list_;                               /* 保持ウイルスのリスト */
    VECTOR(Virus *) stand_by_virus_list_;                      /* 待機ウイルスリスト */
};

#endif
