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

// 自身のタグを突然変異させる
void Gene :: mutation( int prob ) {
  int maxtag = 1;  // 最大タグ
  int len = getLen();  // 遺伝子の長さを取得
  int pos = uniform_int( 0, len-1 );
  setTagNumAt( uniform_int(0, maxtag), pos );
}

void Gene :: initTagRandom() {
  int maxtag = 1;
  FOR( pos, getLen() ) {
    setTagNumAt( uniform_int( 0, maxtag ), pos );
  }
}

int Gene :: getLen() const {
  return tag_.length();
}

std::string& Gene :: getTagString() {
  return tag_;
}

void Gene :: setTagNumAt( int num, int pos ) {
  tag_[pos] = '0' + num;
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
