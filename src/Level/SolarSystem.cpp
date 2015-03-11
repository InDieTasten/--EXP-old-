#include <Level\SolarSystem.hpp>

SolarSystem::SolarSystem(Level* _parent, string* _id)
{
	//pointer
	ID = _id;
	parent = _parent;

	//member
	threadManager = new ThreadManager(this);
}
SolarSystem::~SolarSystem()
{
	//pointer
	ID = nullptr;
	parent = nullptr;

	//member
	delete threadManager;
	threadManager = nullptr;
}