#ifndef ___TCELL_HPP
#define ___TCELL_HPP

#include "Gene.hpp"
#include "Mobile.hpp"
#include "Function.hpp"

class Virus;
class __Landscape;

/**
 * @brief T細胞
 *
 * 遺伝子を持ち、移動できる
 */
class Tcell : public __Life, public __Mobile
{
  public:
    Tcell( const char *tag );
    Tcell( int len );
    virtual ~Tcell() { }

    bool isMemoryTcell() const { return is_memory_tcell_flag_; }
    void becomeMemoryTcell() { is_memory_tcell_flag_ = true; }

    Tcell& clone();                              ///< クローンを作成
    void reborn();                               ///< 再生成

    bool hasReceptorMatching( Virus &v );        ///< ウイルスに対する受容体所持の真偽

    void aging(); ///< 齢を増やす
    int getAge() const { return age_; }
    bool willDie( int max_age ) const; ///< 寿命を超えているか評価
  private:
    int age_;

    bool is_memory_tcell_flag_;
};

#endif
