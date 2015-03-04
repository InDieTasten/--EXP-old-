#ifndef _Level_hpp_
#define _Level_hpp_

#include <map>
#include <Level\SolarSystem.hpp>
//#include <Core\ThreadManager.hpp>
#include <string>

using namespace std;

class Level
{
private:
	std::map<string, SolarSystem*> sytems;
	SolarSystem* currentSystem;
	//ThreadManager* threadHandler;

public:
	Level();
	~Level();

	SolarSystem* getSystem();
	SolarSystem* getSystem(string* _id);

	void addSystem(string* _id);
	void removeSystem(string* _id);
};

#endif // !_Level_hpp_