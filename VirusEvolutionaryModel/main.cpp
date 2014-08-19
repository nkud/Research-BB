#include <iostream>

#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"

using namespace std;

int main() {
  cout << "Virus Evolutionary Model" << endl;

  Term &term = Term::Instance();
  term.setMaxTerm(10);
  while( term.loop() )
  {
    cout << term.getTerm() << endl;
  }
  return 0;
}
