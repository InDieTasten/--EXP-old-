#include <Core\GraphicsThread.hpp>

GraphicsThread::GraphicsThread(ThreadManager* _parent)
{
	//pointer
	parent = _parent;

	ug::log("A GraphicsThread has been constructed");
}