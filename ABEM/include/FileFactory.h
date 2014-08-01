/*
 * =====================================================================================
 *
 *       Filename:  FileFactory.h
 *
 *    Description:  
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___FILEFACTORY
#define ___FILEFACTORY

#include "Config.h"

#include <fstream>

class AgentManager;
class VirusManager;

/*
 * =====================================================================================
 *        Class:  FileFactory
 *  Description:  ファイル出力系関数
 * =====================================================================================
 */
class FileFactory {
  public:
    //-----------------------------------------------------------------------------
    //  初期化
    //-----------------------------------------------------------------------------
    static FileFactory& Instance(); /* インスタンスを返す */
    void setManager( AgentManager &, VirusManager & ); 
    //-----------------------------------------------------------------------------
    //  景観結果出力
    //-----------------------------------------------------------------------------
    void outputFile_VirusDataBase( const char *fname, const char *dirname, int interval ) const; // ウイルスデータベースを出力
    void outputFile_AgentDataBase( const char *fname, const char *dirname, int interval ) const;  // エージェントデータベースを出力

    void outputFile_appendLastInfo( const char * ) const; /* パラメータ情報を出力 */

    void outputValueWithTerm( const char *, int, int interval=1 ) const; // 期間と数値を出力

  private:
    //-----------------------------------------------------------------------------
    //  コンストラクタ
    //-----------------------------------------------------------------------------
    FileFactory( ) {}           /* コンストラクタ */
    //-----------------------------------------------------------------------------
    //  管理者
    //-----------------------------------------------------------------------------
    AgentManager *am_;          /* 管理者を登録 */
    VirusManager *vm_;          /* 管理者を登録 */

};

#endif
