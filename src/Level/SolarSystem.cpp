#include <Level\SolarSystem.hpp>
#include <Level\Level.hpp>
#include <Core\Databank.hpp>

SolarSystem::SolarSystem(Level* _parent, string* _id)
{
	ug::log("[Info]A system is constructing...");

	//pointer
	ID = _id;
	parent = _parent;
	threadManager = nullptr;

	ug::log("[Info]A system has been constructed: " + *_id);
}
SolarSystem::~SolarSystem()
{
	ug::log("[Info]System \"" + *ID + "\" is destructing...");
	//member
	delete threadManager;
	threadManager = nullptr;
	for (auto it : planets)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : bullets)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : constructs)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : ships)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : asteroids)
	{
		delete it;
		it = nullptr;
	}
	for (auto it : debris)
	{
		delete it;
		it = nullptr;
	}

	//pointer
	string* tmp = ID;
	ID = nullptr;
	parent = nullptr;

	ug::log("[Info]A system has been destructed: " + *tmp);
}
string* SolarSystem::getID()
{
	return ID;
}
void SolarSystem::activate()
{
	if (!threadManager)
	{
		threadManager = new ThreadManager(this, parent->getEventThread(), parent->getGraphicsThread());
		parent->getEventThread()->addParent(threadManager);
	}
	else
		ug::log("[Warning]Tried activating already active SolarSystem: " + *ID);
}
void SolarSystem::deactivate()
{
	if (threadManager)
	{
		parent->getEventThread()->removeParent(threadManager);
		delete threadManager;
		threadManager = nullptr;
	}
	else
		ug::log("[Warning]Tried deactivating already deactive SolarSystem: " + *ID);
}
ThreadManager* SolarSystem::getThreadManager()
{
	return threadManager;
}