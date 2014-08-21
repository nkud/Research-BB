#ifndef ___HOST_HPP
#define ___HOST_HPP

class __Host
{
  public:
    __Host();
    ~__Host();
    void clearInfectedViruses();
    void clearStandByViruses();
    VECTOR(Virus *)& getInfectedVirusList();
    VECTOR(Virus *)& getStandByVirusList();
    void pushCloneToStandByVirusList( Virus& v );
    void pushNewVirusToInfectedVirusList( Virus& v );
    bool canPushNewVirus();
  private:
};

#endif
