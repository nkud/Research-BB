#ifndef ___TCELL_HPP
#define ___TCELL_HPP

#include "Gene.hpp"
#include "Mobile.hpp"

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
    ~Tcell();

    Tcell& clone();                              ///< クローンを作成
    void reborn();                               ///< 再生成

    bool hasReceptorMatching( Virus &v );        ///< ウイルスに対する受容体所持の真偽
  private:
};

#endif
