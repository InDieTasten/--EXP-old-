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
	ThreadManager(SolarSystem* _parent, EventThread* _eventThread, GraphicsThread* _graphThread);
	~ThreadManager();

	SolarSystem* getParent();

	void launch();
	void terminate();

	//GraphicsThread
	void startRender(sf::View _view);
	void stopRender();

	//Gravity/Movement Thread
	void startSimulation();
	void incThreads(int _amount);
	void decThreads(int _amount);
	void stopSimulation();
};

#endif // !_ThreadManager_hpp_