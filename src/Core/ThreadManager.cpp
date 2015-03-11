#include <Core\ThreadManager.hpp>
#include <Level\SolarSystem.hpp>

ThreadManager::ThreadManager(SolarSystem* _parent)
{
	parent = _parent;
	eventThread = nullptr;
	ug::log("ThreadManager has been constructed: " + *_parent->getID());
	looptime = chrono::milliseconds(1000 / 100);
	graphThread = new GraphicsThread();
}
ThreadManager::~ThreadManager()
{
	string tmp = *parent->getID();
	//WORK Tell SolarSystem
	parent = nullptr;
	//WORK Tell EventThread
	eventThread = nullptr;
	delete graphThread;
	graphThread = nullptr;
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

		//Gravity(on demand)

		//Modding(on demand)

		//Transfer/Import/Removal/Balancing(on demand)
	}
}