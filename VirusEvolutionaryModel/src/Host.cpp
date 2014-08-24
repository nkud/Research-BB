#include "Host.hpp"
#include "Function.hpp"
#include "Virus.hpp"


VECTOR(Virus *)& __Host :: getInfectedVirusList()
{
  return infected_virus_list_;
}

VECTOR(Virus *)& __Host :: getStandByVirusList()
{
  return stand_by_virus_list_;
}

void __Host :: clearInfectedViruses()
{
  EACH( it_v, getInfectedVirusList() ) {
    SAFE_DELETE( *it_v );
  }
  infected_virus_list_.clear();
}
void __Host :: clearStandByViruses()
{
  EACH( it_v, getStandByVirusList() ) {
    SAFE_DELETE( *it_v );
  }
  stand_by_virus_list_.clear();
}

void __Host :: pushNewVirusCloneToInfectedVirusList( Virus& v )
{
  infected_virus_list_.push_back( v.clone() );
}
void __Host :: pushVirusToStandByVirusList( Virus& v )
{
  stand_by_virus_list_.push_back( v.clone() );
}

bool __Host :: canPushNewVirus()
{
  // 保持ウイルスの最大値があれば、ここで処理
  if( getInfectedVirusListSize() < max_virus_can_have_ )
    return true;
  else
    return false;
}
