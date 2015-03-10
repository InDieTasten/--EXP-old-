#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent, EventThread* _main)
{
	parent = _parent;
	eventThread = _main;
	ug::log("ThreadManager has been constructed: " + *_parent->getID());
}
ThreadManager::~ThreadManager()
{
	string tmp = *parent->getID();
	//Tell SolarSystem
	parent = nullptr;
	//Tell EventThread
	eventThread = nullptr;
	ug::log("ThreadManager has been destructed: " + tmp);
}