#include <iostream>

#include "Config.hpp"
#include "Virus.hpp"
#include "Human.hpp"
#include "Term.hpp"
#include "Cell.hpp"

using namespace std;

const int WIDTH = 30;

int main() {
  cout << "Virus Evolutionary Model" << endl;

  // 初期化
  HumanLand* humanLand = new HumanLand(WIDTH, WIDTH);
  CellLand* cellLand = new CellLand(WIDTH, WIDTH);
  // ウイルスの増殖
  // T細胞の移動
  // T細胞のウイルス殺傷
  // T細胞の寿命
  // T細胞を補完する
  Term &term = Term::Instance();
  term.setMaxTerm(10);

  while( term.loop() )
  {
    cout << term.getTerm() << endl;
  }

  return 0;
}
