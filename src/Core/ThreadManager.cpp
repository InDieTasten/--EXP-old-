#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent, EventThread* _eventThread, GraphicsThread* _graphThread)
{
	//pointer
	parent = _parent;
	eventThread = _eventThread;
	graphThread = _graphThread;
	
	//member
	gravThread = new GravityThread(this);

	//init
	looptime = chrono::milliseconds(1000 / 100);
	running = false;

	ug::log("[Info]ThreadManager has been constructed: " + *_parent->getID());
}
ThreadManager::~ThreadManager()
{
	//stop processed
	stopSimulation();
	stopRender();
	terminate();


	//member
	delete gravThread;
	gravThread = nullptr;


	//pointer
	string tmp = *parent->getID();
	parent = nullptr;
	eventThread = nullptr;

	ug::log("[Info]ThreadManager has been destructed: " + tmp);
}
void ThreadManager::launch()
{
	if (!me.joinable())
	{
		ug::log("[Info]Launching ThreadManager... " + *parent->getID());
		running = true;
		me = thread(&ThreadManager::run, this);
	}
	else {
		ug::log("[Warning]Tried launching already running ThreadManager: " + *parent->getID());
	}
}
void ThreadManager::terminate()
{
	if (me.joinable())
	{
		ug::log("[Info]Terminating ThreadManager... " + *parent->getID());
		running = false;
	}
	else {
		ug::log("[Warning]Tried terminating already stopped ThreadManager: " + *parent->getID());
	}
}
void ThreadManager::run()
{
	ug::log("[Info]ThreadManager is running in this thread");
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (running)
	{
		//Thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();

		//write ghostforces
		//read actions all at once(Gravity, Movement, Graphics)
		//write actions all at once
		//management/balancing/removal/inclusion
	}
	ug::log("[Info]ThreadManager has stopped running in this thread");
}
SolarSystem* ThreadManager::getParent()
{
	return parent;
}
void ThreadManager::startRender(sf::View _view)
{
	if (graphThread)
	{
		if (graphThread->isRunning())
		{
			ug::log("[Warning]ThreadManager will terminate GraphicsThread to re-launch it");
			stopRender();
			startRender(_view);
		}
		else {
			//WORK set graphThread
			graphThread->launch();
		}
	}
	else {
		ug::log("[Warning]ThreadManager couldn't launch GraphicsThread, because it doesn't know one");
	}
}
void ThreadManager::stopRender()
{
	if (graphThread)
	{
		if (graphThread->isRunning())
		{
			graphThread->terminate();
		}
		else {
			ug::log("[Warning]ThreadManager tried to stop already stopped GraphicsThread");
		}
	}
	else {
		ug::log("[Warning]ThreadManager couldn't terminate GraphicsThread, because it doesn't know one");
	}
}
void ThreadManager::startSimulation()
{
	//WORK destribute/assign to gravThread
	//WORK create at least one movementThread
	//WORK distribute/assign elements to movementThread(s)
	//WORK launch everything
}
void ThreadManager::stopSimulation()
{

}