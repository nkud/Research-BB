#ifndef ___FILEFACTORY_HPP
#define ___FILEFACTORY_HPP

class FileFactory
{
  public:
    static FileFactory& Instance();
    void outputValueWithTerm( const char *fname, int term ) const;
  private:
};

#endif
