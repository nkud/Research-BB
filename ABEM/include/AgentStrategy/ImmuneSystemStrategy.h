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
      bool infection( Agent &self, Virus &v );                       /* 感染プロセス  */
      void response( Agent &self );                                  /* 免疫応答する（タグフリップ）  */

      bool hasVirus( Virus & ) const;
      /*-----------------------------------------------------------------------------
       *  保持ウイルス操作セット
       *-----------------------------------------------------------------------------*/
      VirusData *getVirusDataAt( int ) const;                        /* 指定の保持ウイルスを返す */
      int getVirusListSize() const;                                  /* 保持ウイルスのリストを返す */
      void pushVirusData( VirusData * );                             /* 保持ウイルスに追加する */
      void eraseVirusData( std::vector<VirusData *>::iterator );     /* 指定の保持ウイルスを削除する */
      bool hasNoVirusData() const;                                   /* ウイルスを保持していない */
      std::vector<VirusData *>::iterator getVirusListIteratorBegin();  /* 先頭へのイテレータを返す */
      std::vector<VirusData *>::iterator getVirusListIteratorEnd();  /* 末尾へのイテレータを返す */
      /*-----------------------------------------------------------------------------
       *  待機ウイルス操作セット
       *-----------------------------------------------------------------------------*/
      Virus *getStandByVirusAt( int n ) const;                       /* 指定の待機ウイルスを返す */
      void pushStandByVirus( Virus *v );                             /* 待機ウイルスに追加する */
      int getStandByListSize() const;                                /* 待機ウイルスの数を返す */
      bool hasNoStandByVirus() const;                                /* ウイルスを保持していない */
      std::vector<Virus *>::iterator getStandByListIteratorBegin();  /* 先頭へのイテレータを返す */
      std::vector<Virus *>::iterator getStandByListIteratorEnd();    /* 末尾へのイテレータを返す */
      void eraseStandByVirus( std::vector<Virus *>::iterator it );   /* 指定の待機ウイルスを削除 */
      void clearStandByVirus();                                      /* 待機ウイルスをすべて削除 */
    private:
      /*-----------------------------------------------------------------------------
       *  配列
       *-----------------------------------------------------------------------------*/
      std::vector<VirusData *> *vlist_;                              /* 保持ウイルスのリスト */
      std::vector<Virus *> *stand_by_list_;                          /* 待機ウイルスリスト */

      __ImmuneSystemStrategy *immunesystem_strategy_;
};
/*
 * =====================================================================================
 *        Class:  VirusList, VirusData
 *  Description:  エージェントの保持ウイルスデータ
 * =====================================================================================
 */
struct VirusData                                                     /* 保持ウイルスデータ  */
{
  Virus *v_;                                                         /* 保持ウイルスへのポインタ  */
  int sp_;                                                           /* スタートポイント  */

  /*-----------------------------------------------------------------------------
   *  コンストラクタ
   *-----------------------------------------------------------------------------*/
  VirusData(): v_( 0 ), sp_( 0 ) {};                                 /* ウイルスデータを初期化 */
  VirusData( Virus &v, int sp ): v_(&v), sp_(sp) {};
};


/* =====================================================================================
 *        Class:  __ImmuneSystemStrategy
 *  Description:  免疫応答戦略インターフェイス
 * ================================================================================== */
class __ImmuneSystemStrategy {
  public:
    virtual ~__ImmuneSystemStrategy() { };
    virtual void response(Agent &self) = 0;
    virtual bool infection(Agent &self, Virus &v ) = 0;
};

/*-----------------------------------------------------------------------------
 *  タグフリップ
 *-----------------------------------------------------------------------------*/
class TagFlip : public __ImmuneSystemStrategy {
  public:
    virtual void response(Agent &self);
    virtual bool infection(Agent &self, Virus &v );
};

#endif
