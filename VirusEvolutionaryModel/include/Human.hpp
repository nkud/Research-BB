#ifndef ___AGENT_HPP
#define ___AGENT_HPP

#include "Gene.hpp"
#include "Function.hpp"

class Virus;
class ImmuneSystem;

/**
 * @brief ヒト
 */
class Human : public Gene
{
  public:
    Human();
    int getX() const;
    int getY() const;
    void setX( int x );
    void setY( int y );
    void move();

    bool infection( Virus& v );

    void reborn();                // 初期化される
  private:
    int x_, y_;
    ImmuneSystem *immune_system_;
};

class HumanLand
{
  public:
    Human& getHumanAt( int x, int y );
    const VECTOR(Human *) getNeighborsAt( int x, int y ) const;
    VECTOR(Human *) getHumanList();
    int getHumanListSize();

    int getWidth() const;
    int getHeight() const;
    HumanLand( int width, int height );
  private:
    VECTOR(Human *) human_list_;
    int width_;
    int height_;
};

#endif
