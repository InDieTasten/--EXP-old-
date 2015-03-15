#include <Level\SolarSystem.hpp>
#include <Level\Level.hpp>
#include <Core\Databank.hpp>

SolarSystem::SolarSystem(Level* _parent, string* _id)
{
	//pointer
	ID = _id;
	parent = _parent;
	threadManager = nullptr;

	ug::log("[Info]A system has been constructed: " + *_id);
}
SolarSystem::~SolarSystem()
{
	//member
	delete threadManager;
	threadManager = nullptr;

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
		parent->getEventThread()->removeParent(threadmanager);
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