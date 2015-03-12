#include <Core\GraphicsThread.hpp>

GraphicsThread::GraphicsThread(ThreadManager* _parent)
{
	//pointer
	parent = _parent;

	running = false;
	looptime = chrono::milliseconds(1000/40);

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
	running = true;
	me = thread(&GraphicsThread::run, this);
}
void GraphicsThread::run()
{
	ug::log("[Info]GraphicsThread is running in this thread");
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (running)
	{
		//Thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();

	}
	ug::log("[Info]GraphicsThread has stopped running in this thread");
}