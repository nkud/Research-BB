/*
 * =====================================================================================
 *
 *       Filename:  FileFactory.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/08/2013 20:12:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
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
    private:
        FileFactory( ) {}                                            /* コンストラクタ */

        Administrator *admin_;                                       /* 管理者を登録 */

        int last_term_;                                              /* 実際に計算を行った期間 */

        void scriptForPopulationPng(std::ofstream &ofs);             /* 画像を出力するスクリプト */
        void scriptForHasVirusPng(std::ofstream &ofs);
        void scriptForHasImmunityPng(std::ofstream &ofs);
        void scriptForSIRPng(std::ofstream &ofs);
        void scriptForContactPng(std::ofstream &ofs);

    public:
        static FileFactory& Instance();                              /* インスタンスを返す */
        void setAdministrator( Administrator &admin );

        void generatePlotScriptForPng();                             /* プロット用のスクリプトを生成 */
        void generateResultHtml(int last_term);                      /* 結果表示用のHTMLスクリプトを生成 */

        void outputFile_HasVirus( const char * );                    /* ファイルに出力 */
        void outputFile_HasImmunity( const char * );                 /* ファイルに出力 */
        void outputFile_InfectionContactRatio( const char * );       /* ファイルに出力 */
        void outputFile_Population( const char * );                  /* 人口推移を出力 */
        void outputFile_LastLog( const char * );                     /* ログを出力 */
};

#endif
