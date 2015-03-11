#include <Level\SolarSystem.hpp>

SolarSystem::SolarSystem(Level* _parent, string* _id)
{
	//pointer
	ID = _id;
	parent = _parent;

	//member
	threadManager = new ThreadManager(this);
}