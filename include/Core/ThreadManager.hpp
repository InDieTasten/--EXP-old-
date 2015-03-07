#ifndef _ThreadManager_hpp_
#define _ThreadManager_hpp_

#include <Core\GravityThread.hpp>
#include <Core\MovementThread.hpp>
#include <list>
#include <Core\GraphicsThread.hpp>

using namespace std;
extern void ug::log(std::string);

class ThreadManager
{
	SolarSystem* parent;
	GravityThread* gravThread;
	list<MovementThread*>* moveThreads;
	GraphicsThread* graphThread;

public:
	ThreadManager(SolarSystem* _system);
	~ThreadManager();

	void Run();
	void Stop();
};

#endif // !_ThreadManager_hpp_