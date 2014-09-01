#include "Gene.hpp"
#include "Function.hpp"

#include <string>

Gene :: Gene( const char *tag )
{
  tag_ = std::string(tag);                       // 文字列で初期化
}

Gene :: Gene( std::string& tag )
{
  tag_ = std::string(tag);                       // 文字列で初期化
}

Gene :: Gene( int len )
{
  tag_ = std::string(len, '0');                  // 全て０で初期化
  initTagRandom();
}


//--------------------------------------------------------------------------------------
//       Class:  Gene
//      Method:  initTagRandom
// Description:  
//--------------------------------------------------------------------------------------
void Gene :: initTagRandom() {
  int maxtag = 1;
  FOR( pos, getLen() ) {
    setTagNumAt( '0'+uniform_int( 0, maxtag ), pos );
  }
}

int Gene :: getLen() const {
  return tag_.length();
}

std::string& Gene :: getTagString() {
  return tag_;
}

void Gene :: setTagNumAt( int num, int pos ) {
  tag_[pos] = num;
}

bool Gene :: isInclude( Gene& other )
{
  if( getTagString().find( other.getTagString() ) == std::string::npos ) {
    return false;
  } else {
    //DEBUG( getTagString() );
    //DEBUG( other.getTagString() );
    return true;
  }
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
