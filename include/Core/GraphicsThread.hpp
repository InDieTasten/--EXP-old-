#ifndef _GraphicsThread_hpp_
#define _GraphicsThread_hpp_

#include <thread>

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GraphicsThread
{
private:
	ThreadManager* parent;
	thread me;
	void run();

public:
	GraphicsThread();
	~GraphicsThread();

	void launch();
	void terminate();
};

#endif // !_GraphicsThread_hpp_