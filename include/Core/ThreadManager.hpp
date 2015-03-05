#ifndef _ThreadManager_hpp_
#define _ThreadManager_hpp_

#include <Core\GravityThread.hpp>
#include <Core\MovementThread.hpp>
#include <list>
#include <Core\GraphicsThread.hpp>
#include <Level\SolarSystem.hpp>

class ThreadManager
{
	SolarSystem* parent;
	GravityThread* gravThread;
	std::list<MovementThread*>* moveThreads;
	GraphicsThread* graphThread;

public:
	ThreadManager(SolarSystem* _system);
	~ThreadManager();

	void Run();
	void Stop();
};

#endif // !_ThreadManager_hpp_