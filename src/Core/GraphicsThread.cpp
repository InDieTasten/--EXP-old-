#include <Core\GraphicsThread.hpp>

GraphicsThread::GraphicsThread(sf::RenderWindow* _renderWindow)
{
	//pointer
	renderWindow = _renderWindow;

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
	if (isRunning())
	{
		ug::log("[Warning]Tried to launch already running GraphicsThread");
	}
	else {
		running = true;
		me = thread(&GraphicsThread::run, this);
	}
}
void GraphicsThread::run()
{
	ug::log("[Info]GraphicsThread is running in this thread");
	renderWindow->setActive(true);
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (running)
	{
		//Thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();

		renderWindow->clear(sf::Color(10, 10, 10, 10));
		renderWindow->display();
	}
	renderWindow->setActive(false);
	ug::log("[Info]GraphicsThread has terminated");
}
bool GraphicsThread::isRunning()
{
	return me.joinable();
}
void GraphicsThread::terminate()
{
	ug::log("[Info]Terminating GraphicsThread...");
	running = false;
	me.join();
}