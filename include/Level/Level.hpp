#ifndef _Level_hpp_
#define _Level_hpp_

#include <Utilities\Logger.hpp>
#include <unordered_map>
#include <Level\SolarSystem.hpp>
#include <string>

using namespace std;
extern void ug::log(std::string);

class Databank;

class Level
{
private:
	Databank* parent;
	unordered_map<string*, SolarSystem*> systems;
	EventThread* eventThread;
	GraphicsThread* graphThread;

public:
	Level(Databank* _parent, EventThread* _eventThread, GraphicsThread* _graphThread);
	~Level();

	SolarSystem* getSystem(string _id);
	Databank* getParent();

	void addSystem(string* _id);
	void removeSystem(string* _id);
};

#endif // !_Level_hpp_