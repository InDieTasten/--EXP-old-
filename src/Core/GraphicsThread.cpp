#include <Core\GraphicsThread.hpp>

GraphicsThread::GraphicsThread(ThreadManager* _parent)
{
	//pointer
	parent = _parent;

	ug::log("[Info]A GraphicsThread has been constructed");
}
GraphicsThread::~GraphicsThread()
{
	//pointer
	parent = nullptr;

	ug::log("[Info]A GraphicsThread has been destructed");
}
void GraphicsThread::launch()
{
	me = thread(&GraphicsThread::run, this);
}