#ifndef ___MOBILE_HPP
#define ___MOBILE_HPP

#include "Landscape.hpp"
#include "Function.hpp"

class __Landscape;
class __Location;
class __Mobile;

class __Location
{
  public:
    __Location( int x, int y ) : x_(x), y_(y) { }
    virtual int getX() { return x_; }
    virtual int getY() { return y_; }
    virtual void setX( int x ) { x_ = x; }
    virtual void setY( int y ) { y_ = y; }
    void randomLocate( __Landscape& land ) {
      int w = land.getWidth();
      int h = land.getHeight();
      setX( uniform_int(0,w-1) );
      setY( uniform_int(0,h-1) );
    }
  private:
    int x_, y_;
};

class __Mobile : public __Location
{
  public:
    __Mobile( int x, int y ) : __Location(x, y) { }
    virtual void move( __Landscape& land ) {
      int x = getX();
      int y = getY();
      if( rand_bool() )
        x += rand_bool() ? 1 : -1;
      if( rand_bool() )
        y += rand_bool() ? 1 : -1;
      //x += land.getWidth();
      //y += land.getHeight();
      //setX( x%land.getWidth() );
      //setY( y%land.getHeight() );
      x = std::max( x, 0 );
      setX( x%land.getWidth() );
      setY( y%land.getHeight() );
    }
  private:
};

#endif
