#ifndef _GraphicsThread_hpp_
#define _GraphicsThread_hpp_

#include <Utilities\Logger.hpp>
#include <thread>

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GraphicsThread
{
private:
	ThreadManager* parent;
	thread me;

	chrono::milliseconds looptime;
	bool running;
	void run();

public:
	GraphicsThread(ThreadManager* _parent);
	~GraphicsThread();

	void launch();
	void terminate();
};

#endif // !_GraphicsThread_hpp_