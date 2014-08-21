#include "Function.hpp"
#include "Random.hpp"

bool probability( double prob )
{
  if( prob > uniform_double( 0, 100 ) ) {
    return true;
  } else {
    return false;
  }
}

int uniform_int(int a, int b) {
  return Random::Instance().uniformInt(a, b);
}

double uniform_double(double a, double b) {
  return Random::Instance().uniformDouble(a, b);
}
bool rand_bool()
{
  return probability(50) ? true : false;
}
