#ifndef ___VIRUS_COUNTER_HPP
#define ___VIRUS_COUNTER_HPP

#include <map>

class Virus;

class VirusCounter
{
  public:
  	static VirusCounter& Instance() {
  		static VirusCounter singleton;
  		return singleton;
  	}

  	void clearData();

  	void addNewVirusData( Virus& virus ); // 新しいウイルスのデータを追加

  	std::map<int, int>& getVirusValueMap() { return virus_value_map_; }
  private:
  	VirusCounter() { }

  	std::map<int, int> virus_value_map_;
};

#endif
