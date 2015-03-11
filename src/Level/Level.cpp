#include <Level\Level.hpp>

Level::Level(Databank* _parent)
{
	//pointer
	parent = _parent;
	currentSystem = nullptr;

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
SolarSystem* Level::getSystem(string _id)
{
	for (auto it : systems)
	{
		if (*it.second->getID() == _id)
		{
			return it.second;
		}
	}
	ug::log("[Warning] Level::getSystem(string _id) has to return a nullpointer");
	return nullptr;
}
void Level::addSystem(string* _id)
{
	if (getSystem(*_id))
	{
		ug::log("[Warning] Level::addSystem aborts routine of already allocated id: " + *_id);
	}
	string* tmp = new string(*_id);
	systems.insert(pair<string*, SolarSystem*>(tmp, new SolarSystem(this, tmp)));
	ug::log("Level registered new System: " + *_id);
}
void Level::removeSystem(string* _id)
{
	SolarSystem* n = getSystem(*_id);
	if (n)
	{
		string* tmp = n->getID();
		systems.erase(tmp);
		delete n;
		delete tmp;
		ug::log("Level removed System: " + *_id);
	}
	else {
		ug::log("[Warning] Couldn't find system to remove: " + *_id);
	}
}
Databank* Level::getParent()
{
	return parent;
}