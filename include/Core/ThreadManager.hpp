#ifndef _ThreadManager_hpp_
#define _ThreadManager_hpp_

#include <Core\EventThread.hpp>
#include <Core\GravityThread.hpp>
#include <Core\MovementThread.hpp>
#include <list>
#include <Core\GraphicsThread.hpp>
#include <thread>

using namespace std;
extern void ug::log(std::string);

class SolarSystem;

class ThreadManager
{
	SolarSystem* parent;
	EventThread* eventThread;
	GravityThread gravThread;
	list<MovementThread> moveThreads;
	GraphicsThread graphThread;
	thread me;
	void run();

public:
	ThreadManager(SolarSystem* _system, EventThread* _main);
	~ThreadManager();

	void launch();
	void terminate();
};

#endif // !_ThreadManager_hpp_