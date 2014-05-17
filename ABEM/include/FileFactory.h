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

#include <fstream>

class Administrator;

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
        void setAdministrator( Administrator &admin ); 
        /*-----------------------------------------------------------------------------
         *  計算結果出力
         *-----------------------------------------------------------------------------*/
        void outputFile_HasVirus( const char * ) const;              /* ウイルス保持者出力 */
        void outputFile_HasImmunity( const char * ) const;           /* ファイルに出力 */
        void outputFile_InfectionContactRatio( const char * ) const; /* ファイルに出力 */
        void outputFile_Population( const char * ) const;            /* 人口推移を出力 */
        void outputFile_LastLog( const char * ) const;               /* ログを出力 */
        void outputFile_Info( const char * ) const;                  /* パラメータ情報を出力 */
        double outputFile_peakSearch( const char * ) const;          /* 出力: ピークサーチ */

    private:
        /*-----------------------------------------------------------------------------
         *  コンストラクタ
         *-----------------------------------------------------------------------------*/
        FileFactory( ) {}                                            /* コンストラクタ */
        Administrator *admin_;                                       /* 管理者を登録 */
        int last_term_;                                              /* 実際に計算を行った期間 */

};


/*-----------------------------------------------------------------------------
 *  関数群
 *-----------------------------------------------------------------------------*/
//static int max_term_in_interval( const int data[], int cursor, int len );   /* 与えられた期間の最大時刻を探索する */
//static double average_period( const char *fname );                   /* ファイルの平均周期を求める */

#endif
