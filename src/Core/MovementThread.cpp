#include <Core\MovementThread.hpp>
#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

MovementThread::MovementThread(ThreadManager* _parent)
{
	//pointer
	parent = _parent;

	ug::log("A MovementThread has been constructed: " + *parent->getParent()->getID());
}