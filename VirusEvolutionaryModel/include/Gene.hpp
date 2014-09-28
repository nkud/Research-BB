#ifndef ___GENE_HPP
#define ___GENE_HPP

#include <string>
#include "Function.hpp"

/**
 * @brief 遺伝子
 */
class Gene
{
 public:
  Gene( const char *tag );                     ///< タグを指定して初期化
  Gene( std::string& tag );                    ///< タグを指定して初期化
  Gene( int len );                             ///< タグの長さを指定して初期化
  ~Gene() { }

  bool isInclude( Gene& other );               ///< タグを含んでいるか評価
  bool hasEqualTagTo( Gene& other );           ///< タグが等しいか評価

  void initTagRandom();                        ///< タグをランダムに設定

  std::string& getTagString();                 ///< タグの文字列を取得する
  int getTagNumAt( int pos );                  ///< 指定された位置のタグを取得する
  void setTagNumAt( int num, int pos );
  int getLen() const;                          ///< タグの長さを取得する
  void mutation( int prob );                    ///< 突然変異する
  const char *getCString() { return tag_.c_str(); }

  int value();

  int minimumHammingDistanceFor( Gene& other );  ///< 最小ハミング距離を返す

 private:
  std::string tag_;                            ///< タグ
};

/**
 * @brief 遺伝子を持つ生命体
 */
class __Life 
{
 public:
  __Life( const char *tag );
  __Life( int len );
  ~__Life() { SAFE_DELETE( gene_ ); }

  __Life& clone();                               ///< クローンを作成する
  Gene& getGene() { return *gene_; }             ///< 遺伝子を取得する
 private:
  Gene *gene_;
};

#endif
