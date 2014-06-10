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
        /*-----------------------------------------------------------------------------
         *  初期化
         *-----------------------------------------------------------------------------*/
        static FileFactory& Instance();                              /* インスタンスを返す */
        void setManager( AgentManager &, VirusManager & ); 
        /*-----------------------------------------------------------------------------
         *  計算結果出力
         *-----------------------------------------------------------------------------*/
        void outputFile_VirusVariaty( const char * ) const;
        void outputFile_LastVirusDataBase( const char * ) const;
        void outputFile_AgentGeneDistribution( const char *);
        void outputFile_LastLog( const char * ) const;               /* ログを出力 */
        void outputFile_Info( const char * ) const;                  /* パラメータ情報を出力 */
        double outputFile_peakSearch( const char * ) const;          /* 出力: ピークサーチ */

        void outputValueWithTerm( const char *, int, int interval=OUTPUT_INTERVAL ) const;

    private:
        /*-----------------------------------------------------------------------------
         *  コンストラクタ
         *-----------------------------------------------------------------------------*/
        FileFactory( ) {}                                            /* コンストラクタ */

        AgentManager *am_;                                           /* 管理者を登録 */
        VirusManager *vm_;                                           /* 管理者を登録 */

};

#endif
