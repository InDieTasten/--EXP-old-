#include <Level\Level.hpp>

Level::Level(Databank* _parent, EventThread* _eventThread, GraphicsThread* _graphThread)
{
	//pointer
	parent = _parent;
	eventThread = _eventThread;
	graphThread = _graphThread;

	ug::log("[Info]A level has been constructed");
}
Level::~Level()
{
	//member
	for (auto it : systems)
	{
		delete it.second;
		it.second = nullptr;
	}
	for (auto it : systems)
	{
		delete it.first;
	}
	

	//pointer
	parent = nullptr;
	eventThread = nullptr;
	graphThread = nullptr;

	ug::log("[Info]A level has been destructed");
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
	ug::log("[Warning]Level::getSystem(\"" + _id + "\") has to return a nullpointer");
	return nullptr;
}
void Level::addSystem(string* _id)
{
	if (getSystem(*_id))
	{
		ug::log("[Warning]Level::addSystem aborts routine of already allocated id: " + *_id);
	}
	string* tmp = new string(*_id);
	systems.insert(pair<string*, SolarSystem*>(tmp, new SolarSystem(this, tmp)));
	ug::log("[Info]Level registered new System: " + *_id);
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
		ug::log("[Info]Level removed System: " + *_id);
	}
	else {
		ug::log("[Warning]Couldn't find system to remove: " + *_id);
	}
}
Databank* Level::getParent()
{
	return parent;
}
EventThread* Level::getEventThread()
{
	return eventThread;
}
GraphicsThread* Level::getGraphicsThread()
{
	return graphThread;
}