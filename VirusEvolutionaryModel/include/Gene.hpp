#ifndef ___GENE_HPP
#define ___GENE_HPP

#include <string>

/**
 * @brief 遺伝子
 */
class Gene
{
 public:
  std::string getTagString();  // タグの文字列を取得する
  int getTagNumAt( int pos );  // 指定された位置のタグを取得する
  int getLen();                // タグの長さを取得する
  int mutation( int prob );    // 確率
  bool hasEqualTagTo( Gene& other );  // タグが等しいか評価
 private:
  std::string tag_;  // タグ
};

/**
 * @brief 遺伝子を持つ生命体
 */
class Life
{
 public:
  Life& clone();
  Gene& getGene() { return *gene_; }
 private:
  Gene *gene_;
};

#endif
