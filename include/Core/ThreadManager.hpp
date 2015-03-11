#ifndef _ThreadManager_hpp_
#define _ThreadManager_hpp_

#include <Core\EventThread.hpp>
#include <Core\GravityThread.hpp>
#include <Core\MovementThread.hpp>
#include <list>
#include <Core\GraphicsThread.hpp>
#include <thread>
#include <chrono>

using namespace std;
extern void ug::log(std::string);

class SolarSystem;

class ThreadManager
{
	SolarSystem* parent;
	EventThread* eventThread;
	GravityThread* gravThread;
	list<MovementThread> moveThreads;
	GraphicsThread* graphThread;

	thread me;
	chrono::milliseconds looptime;
	bool running;

	void run();

public:
	ThreadManager(SolarSystem* _parent, EventThread* _main);
	~ThreadManager();

	SolarSystem* getParent();

	void launch();
	void terminate();
};

#endif // !_ThreadManager_hpp_