#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent, EventThread* _main)
{
	//pointer
	parent = _parent;
	eventThread = _main;
	
	//member
	graphThread = new GraphicsThread(this);
	gravThread = new GravityThread(this);

	//init
	looptime = chrono::milliseconds(1000 / 100);

	ug::log("ThreadManager has been constructed: " + *_parent->getID());
}
ThreadManager::~ThreadManager()
{
	//pointer
	string tmp = *parent->getID();
	parent = nullptr;
	eventThread = nullptr;

	//member
	delete graphThread;
	graphThread = nullptr;
	delete gravThread;
	gravThread = nullptr;

	ug::log("ThreadManager has been destructed: " + tmp);
}
void ThreadManager::launch()
{
	me = thread(&ThreadManager::run, this);
	running = true;
}
void ThreadManager::terminate()
{
	running = false;
}
void ThreadManager::run()
{
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (running)
	{
		//Thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();

		//Movement(always)
		//Graphics(always)
		//Gravity(on demand)
		//Modding(on demand)

		//Transfer/Import/Removal/Balancing(on demand)
	}
}
SolarSystem* ThreadManager::getParent()
{
	return parent;
}