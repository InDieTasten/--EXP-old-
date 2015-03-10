#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent, EventThread* _main)
{
	parent = _parent;
	eventThread = _main;
	ug::log("ThreadManager has been constructed: " + *_parent->getID());
}
