#include <Level\SolarSystem.hpp>

SolarSystem::SolarSystem(Level* _parent, string* _id)
{
	//pointer
	ID = _id;
	parent = _parent;

	//member
	threadManager = new ThreadManager(this);

	ug::log("A system has been constructed: " + *_id);
}
SolarSystem::~SolarSystem()
{
	//pointer
	string* tmp = ID;
	ID = nullptr;
	parent = nullptr;

	//member
	delete threadManager;
	threadManager = nullptr;

	ug::log("A system has been destructed: " + *tmp);
}
string* SolarSystem::getID()
{
	return ID;
}