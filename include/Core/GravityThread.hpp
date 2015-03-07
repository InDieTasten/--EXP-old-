#ifndef _GravityThread_hpp_
#define _GravityThread_hpp_

#include <thread>

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GravityThread
{
private:
	ThreadManager* parent;
	thread me;
	void run();

public:
	GravityThread();
	~GravityThread();

	void launch();
	void terminate();
};

#endif // !_GravityThread_hpp_