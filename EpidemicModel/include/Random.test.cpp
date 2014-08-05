#include "Random.hpp"
#include <iostream>
using namespace std;

int main() {
  cout << "test" << endl;
  for( int i=0; i<10; i++ )
    cout << Random::Instance().randomInt() << endl;
  for( int i=0; i<10; i++ )
    cout << Random::Instance().uniformDouble(0, 1) << endl;
  for( int i=0; i<10; i++ )
    cout << Random::Instance().uniformDouble(0, 100) << endl;
}
