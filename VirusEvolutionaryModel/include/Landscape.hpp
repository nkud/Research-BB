#ifndef ___LANDSCAPE_HPP
#define ___LANDSCAPE_HPP

class __Landscape
{
  public:
    __Landscape( int w, int h ) { width_ = w; height_ = h; }
    virtual int getWidth() { return width_; }
    virtual int getHeight() { return height_; }
    virtual void setWidth( int w ) { width_ = w; }
    virtual void setHeight( int h ) { height_ = h; }
  private:
    int width_;
    int height_;
};

#endif
