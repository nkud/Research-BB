#include "VirusCounter.hpp"
#include "Virus.hpp"

void VirusCounter :: clearData()
{
	virus_value_map_.clear();
}

void VirusCounter :: addNewVirusData( Virus& virus )
{
	int value = virus.value();
	virus_value_map_[value]++;
}

