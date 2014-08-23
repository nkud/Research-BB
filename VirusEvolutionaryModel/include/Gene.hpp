#ifndef ___GENE_HPP
#define ___GENE_HPP

#include <string>

/**
 * @brief 遺伝子
 */
class Gene
{
  public:
    Gene();
    std::string getTagString();                  ///< タグの文字列を取得する
    int getTagNumAt( int pos );                  ///< 指定された位置のタグを取得する
    int getLen();                                ///< タグの長さを取得する
    int mutation( int prob );                    ///< 突然変異する
    bool hasEqualTagTo( Gene& other );           ///< タグが等しいか評価
  private:
    std::string tag_;  // タグ
};

/**
 * @brief 遺伝子を持つ生命体
 */
class __Life 
{
 public:
  __Life& clone();                               ///< クローンを作成する
  Gene& getGene() { return *gene_; }             ///< 遺伝子を取得する
 private:
  Gene *gene_;
};

#endif
