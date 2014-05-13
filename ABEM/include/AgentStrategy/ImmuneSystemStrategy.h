#ifndef ___IMMUNESYSTEM_STRATEGY
#define ___IMMUNESYSTEM_STRATEGY

struct VirusData;
class Agent;
class __ImmuneSystemStrategy;
class Tag;

class ImmuneSystem {
  public:
    /*-----------------------------------------------------------------------------
     *  コンストラクタ・デストラクタ
     *-----------------------------------------------------------------------------*/
    ImmuneSystem();
    ~ImmuneSystem();
    /*-----------------------------------------------------------------------------
     *  免疫機構操作
     *-----------------------------------------------------------------------------*/
    bool infection( Agent &self, Virus &v );                         /* 感染プロセス  */
    int response( Agent &self );                                     /* 免疫応答する（タグフリップ）  */

    bool hasVirus( Virus & );
    void incrementInfectionTime();
    int getInfectionTime() const;
    void resetInfectionTime();
    /*-----------------------------------------------------------------------------
     *  保持ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    Virus *getVirusAt( int ) const;                                  /* 指定の保持ウイルスを返す */
    Virus *getOnSetVirusAt( int );
    int getVirusListSize() const;                                    /* 保持ウイルスのリストを返す */
    int getOnSetVirusListSize();
    void pushVirus( Virus * );                                       /* 保持ウイルスに追加する */
    void eraseVirus( std::vector<Virus *>::iterator );               /* 指定の保持ウイルスを削除する */
    bool hasNoVirus() const;                                         /* ウイルスを保持していない */
    std::vector<Virus *>::iterator getVirusListIteratorBegin();      /* 先頭へのイテレータを返す */
    std::vector<Virus *>::iterator getVirusListIteratorEnd();        /* 末尾へのイテレータを返す */
    /*-----------------------------------------------------------------------------
     *  待機ウイルス操作セット
     *-----------------------------------------------------------------------------*/
    Virus *getStandByVirusAt( int n ) const;                         /* 指定の待機ウイルスを返す */
    void pushStandByVirus( Virus *v );                               /* 待機ウイルスに追加する */
    int getStandByVirusListSize() const;                             /* 待機ウイルスの数を返す */
    bool hasNoStandByVirus() const;                                  /* ウイルスを保持していない */
    std::vector<Virus *>::iterator getStandByVirusListIteratorBegin(); /* 先頭へのイテレータを返す */
    std::vector<Virus *>::iterator getStandByVirusListIteratorEnd(); /* 末尾へのイテレータを返す */
    void eraseStandByVirus( std::vector<Virus *>::iterator it );     /* 指定の待機ウイルスを削除 */
    void clearStandByVirus();                                        /* 待機ウイルスをすべて削除 */
  private:
    /*-----------------------------------------------------------------------------
     *  パラメータ
     *-----------------------------------------------------------------------------*/
    int infection_time_;                                             /* 感染期間 */
    /*-----------------------------------------------------------------------------
     *  配列
     *-----------------------------------------------------------------------------*/
    std::vector<Virus *> *virus_list_;                               /* 保持ウイルスのリスト */
    std::vector<Virus *> *stand_by_virus_list_;                      /* 待機ウイルスリスト */

    __ImmuneSystemStrategy *immunesystem_strategy_;
};
/*
 * =====================================================================================
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 *                XXX: ウイルスクラスにまとめるべきか
 * =====================================================================================
 */
//struct VirusData                                                     /* 保持ウイルスデータ  */
//{
//  Virus *v_;                                                         /* 保持ウイルスへのポインタ  */
//  int sp_;                                                           /* スタートポイント  */
//  int infection_time_;                                               /* ウイルス感染期間 */
//
//  /*-----------------------------------------------------------------------------
//   *  コンストラクタ
//   *-----------------------------------------------------------------------------*/
//  VirusData(): v_( 0 ), sp_( 0 ), infection_time_( 0 ) {};                                 /* ウイルスデータを初期化 */
//  VirusData( Virus &v, int sp, int it ): v_(&v), sp_(sp), infection_time_(it) {};
//};


/* =====================================================================================
 *        Class:  __ImmuneSystemStrategy
 *  Description:  免疫応答戦略インターフェイス
 * ================================================================================== */
class __ImmuneSystemStrategy {
  public:
    virtual ~__ImmuneSystemStrategy() { };
    virtual int response(Agent &self) = 0;
    virtual bool infection(Agent &self, Virus &v ) = 0;
};

/*-----------------------------------------------------------------------------
 *  タグフリップ
 *-----------------------------------------------------------------------------*/
class TagFlip : public __ImmuneSystemStrategy {
  public:
    virtual int response(Agent &self);
    virtual bool infection(Agent &self, Virus &v );
};

#endif
