#ifndef _Level_hpp_
#define _Level_hpp_

#include <map>
#include <Level\SolarSystem.hpp>
#include <string>

using namespace std;
extern void ug::log(std::string);

class Level
{
private:
	map<string*, SolarSystem*>* sytems;
	SolarSystem* currentSystem;

public:
	Level();
	~Level();

	SolarSystem* getSystem();
	SolarSystem* getSystem(string* _id);

	void addSystem(string* _id);
	void removeSystem(string* _id);
};

#endif // !_Level_hpp_