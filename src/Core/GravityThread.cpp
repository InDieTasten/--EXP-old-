#include <Core\GravityThread.hpp>
#include <Core\ThreadManager.hpp>

GravityThread::GravityThread(ThreadManager* _parent)
{
	//pointer
	parent = _parent;

	ug::log("A GravityThread has been constructed: " + *parent->getParent()->getID);
}