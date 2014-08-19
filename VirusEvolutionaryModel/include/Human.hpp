#ifndef ___AGENT_HPP
#define ___AGENT_HPP

#include "Gene.hpp"
#include "Function.hpp"

/**
 * @brief ヒト
 */
class Human : public Gene
{
  public:
    int getX();
    int getY();
    void setX();
    void setY();
    void move();

    void reborn();                // 初期化される
  private:
    int x_, y_;
};

class HumanLand
{
  public:
    Human& getHumanAt( int x, int y );
    VECTOR(Human *) neighbors( int x, int y );
    VECTOR(Human *) getHumanList();
    int getHumanListSize();

    int getWidth();
  private:
    VECTOR(Human *) human_list_;
    int width_;
};

#endif
