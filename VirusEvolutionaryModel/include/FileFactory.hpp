#ifndef ___FILEFACTORY_HPP
#define ___FILEFACTORY_HPP

#include "Function.hpp"
#include "Term.hpp"
#include <fstream>

template < typename T >
void output_value_with_term( const char *fname, T value ) {
  int term = Term::Instance().getTerm();
  std::ofstream ofs(fname, std::ios_base::out | std::ios_base::app);
  ofs << term << SEPARATOR;                      // 期間と
  ofs << value << ENDL;                          // 数値を出力
};

/// ファイル生成クラス
class FileFactory
{
  public:
    static FileFactory& Instance();
    void outputValueWithTerm( const char *fname, int term ) const;
  private:
};

#endif
