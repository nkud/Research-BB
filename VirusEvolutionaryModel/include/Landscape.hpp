#ifndef ___LANDSCAPE_HPP
#define ___LANDSCAPE_HPP

/// 土地インターフェイス
class __Landscape
{
  public:
    __Landscape( int w, int h ) { width_ = w; height_ = h; }

    virtual int getWidth() const { return width_; }
    virtual int getHeight() const { return height_; }
    virtual void setWidth( int w ) { width_ = w; }
    virtual void setHeight( int h ) { height_ = h; }

    bool isOnMap( int x, int y ) {
      if( x < 0 ) { return false; }
      if( y < 0 ) { return false; }
      if( x > getWidth()-1 ) { return false; }
      if( y > getHeight()-1 ) { return false; }
      return true;
    }
//    void returnOnMap( int x, int y );

  private:
    int width_;
    int height_;
};

#endif
