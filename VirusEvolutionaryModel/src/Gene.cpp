#include "Gene.hpp"

#include <string>

Gene :: Gene( const char *tag )
{
  tag_ = std::string(tag);                       // 文字列で初期化
}

Gene :: Gene( int len )
{
  tag_ = std::string(len, '0');                  // 全て０で初期化
}

int Gene :: getLen() const {
  return tag_.length();
}

//----------------------------------------------------------------------
//  __Life
//----------------------------------------------------------------------
__Life :: __Life( const char *tag ) :
  gene_( new Gene(tag) )
{
}
__Life :: __Life( int len ) :
  gene_( new Gene(len) )
{

}
