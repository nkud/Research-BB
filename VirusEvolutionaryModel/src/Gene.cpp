#include "Gene.hpp"
#include "Function.hpp"

#include <string>

Gene :: Gene( const char *tag )
{
  tag_ = std::string(tag);                       // 文字列で初期化
}

int Gene :: value() {
  int sum = 0;
  FOR( i, getLen() ) {
    sum += getTagNumAt(i);
  }
  return sum;
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
  if( probability( prob ) ) 
  {
    // int maxtag = 1;  // 最大タグ
    // int len = getLen();  // 遺伝子の長さを取得
    // int pos = uniform_int( 0, len-1 );
    // setTagNumAt( uniform_int(0, maxtag), pos );
    switch( uniform_int(0, 3) )
    {
      case 0:
      getTagString().insert(0, rand_bool()?"0":"1");
      break;

      case 1:
      getTagString().erase( getTagString().begin() );
      break;
      
      case 2:
      getTagString() += rand_bool()?"0":"1";
      break;

      case 3:
      getTagString().erase( --getTagString().end() );
      break;
      
      default:
      break;
    }
  }
}

int Gene :: getTagNumAt( int pos )
{
  ASSERT( pos < getLen() );
  char c = tag_[ pos ];
  return c - '0';
}

int Gene :: minimumHammingDistanceFor( Gene& other ) {
  // todo
  int self_len = getLen();
  int other_len = other.getLen();
  int diff;
  int sum = 0;
  int min = 0;
  if( self_len > other_len )
  {  // 自分の遺伝子長の方が長ければ
    diff = self_len - other_len;
    min = ++self_len;
    FOR( i, diff+1 )
    {
      sum = 0;
      FOR( j, other_len )
      {
        if( getTagNumAt(i+j) != other.getTagNumAt(j) ) {
          sum++;
        }
      }
      if( sum < min ) {
        min = sum;
      }
    }
  }
  else
  {  // そうでなければ
    diff = other_len - self_len;
    min = ++other_len;
    FOR( i, diff+1 )
    {
      sum = 0;
      FOR( j, self_len ) {
        if( getTagNumAt(j) != other.getTagNumAt(i+j) ) {
          sum++;
        }
      }
      if( sum < min ) {
        min = sum;
      }
    }
  }
  return min;
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
