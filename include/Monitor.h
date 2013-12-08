/*
 * =====================================================================================
 *
 *       Filename:  Monitor.h
 *
 *    Description:  モニター
 *
 *         Author:  Naoki Ueda
 *   Organization:  OPU, 3G
 *
 * =====================================================================================
 */

#ifndef ___MONITOR
#define ___MONITOR

#include <map>
#include <fstream>

#include "Administrator.h"

#ifdef __unix__
#include <sys/time.h>
#endif

class __TagInterface;

/*
 * =====================================================================================
 *        Class:  Monitor
 *  Description:  ( シングルトンパターン )
 * =====================================================================================
 */
class Monitor {
    private:
        Monitor() {}                                                 /* コンストラクタ */

        int num_contact_;                                            /* 接触回数 */
        std::map<__TagInterface *, int> num_infection_contact_;      /* 感染させた接触回数 */

//        int last_term_;
//
//        void scriptForPopulationPng(std::ofstream &ofs);             /* 画像を出力するスクリプト */
//        void scriptForHasVirusPng(std::ofstream &ofs);
//        void scriptForHasImmunityPng(std::ofstream &ofs);
//        void scriptForSIRPng(std::ofstream &ofs);
//        void scriptForContactPng(std::ofstream &ofs);

    public:
        static Monitor& Instance();                                  /* インスタンスを返す */

        /* ゲッタ */
        int getContactNum() const;                                   /* 接触回数を返す */
        int getInfectionContactNum( __TagInterface * );              /* 指定のウイルスの感染接触回数を返す */

        /* カウント */
        void countUpContact();                                       /* 接触しした回数 */
        void countUpInfectionContact( __TagInterface * );            /* 感染のために接触してあるウイルスに感染した回数 */

        void resetAll();                                             /* 値をすべてリセット */

//        void generatePlotScript();                                   /* プロット用のスクリプトを生成 */
//        void generatePlotScriptForPng();                             /* プロット用のスクリプトを生成 */
//        void generateResultHtml(int t);                              /* 結果表示用のHTMLスクリプトを生成 */
};

/*
 * =====================================================================================
 *        Class:  FileFactory
 *  Description:  ファイル出力系関数
 * =====================================================================================
 */
//class FileFactory {
//    private:
//        FileFactory( ) {}                                            /* コンストラクタ */
//
//        Administrator *admin_;                                       /* 管理者を登録 */
//
//        int last_term_;
//
//        void scriptForPopulationPng(std::ofstream &ofs);             /* 画像を出力するスクリプト */
//        void scriptForHasVirusPng(std::ofstream &ofs);
//        void scriptForHasImmunityPng(std::ofstream &ofs);
//        void scriptForSIRPng(std::ofstream &ofs);
//        void scriptForContactPng(std::ofstream &ofs);
//    public:
//        static FileFactory& Instance();                            /* インスタンスを返す */
//        void setAdministrator( Administrator &admin );
//
//        void generatePlotScript();                                   /* プロット用のスクリプトを生成 */
//        void generatePlotScriptForPng();                             /* プロット用のスクリプトを生成 */
//        void generateResultHtml(int t);                              /* 結果表示用のHTMLスクリプトを生成 */
//
//        void outputFile_HasVirus( const char * );                    /* ファイルに出力 */
//        void outputFile_HasImmunity( const char * );                 /* ファイルに出力 */
//        void outputFile_InfectionContactRatio( const char * );       /* ファイルに出力 */
//        void outputFile_LastLog( const char * );                     /* ログを出力 */
//        void outputFile_Population( const char * );                  /* 人口推移を出力 */
//
//
//};

#ifdef __unix__
/*
 * =====================================================================================
 *        Class:  Benchmark
 *  Description:  ベンチマーク
 *                シングルトンパターン
 * =====================================================================================
 */
class Benchmark {
    private:
        Benchmark() {}

        struct timeval tv_;                                          /* 計測開始時間 */
        double start_;                                               /* 計測終了時間 */
        double end_;
    public:
        static Benchmark& Instance();                                /* インスタンスを返す */

        void startTimer();                                           /* 計測開始する */
        void stopTimer();                                            /* 計測終了する */

        double getTime() const;                                      /* 計測時間を返す */
        void printTime() const;                                      /* 計測時間を表示 */
        void printElapsedTime();                                     /* 計測時間を表示 */
};
#endif

#endif
