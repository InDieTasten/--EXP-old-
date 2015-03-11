#include <Level\Level.hpp>

Level::Level(Databank* _parent)
{
	//pointer
	parent = _parent;
	currentSystem = nullptr;

	//default level


	ug::log("A level has been constructed");
}
Level::~Level()
{
	//pointer
	parent = nullptr;
	ug::log("A level has been destructed");
}
SolarSystem* Level::getSystem()
{
	if (currentSystem)
	{
		return currentSystem;
	}
	else {
		ug::log("[Warning] Level::getSystem() has to return a nullpointer");
		return currentSystem;
	}
}