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
