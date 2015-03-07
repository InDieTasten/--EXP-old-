#ifndef _MovementThread_hpp_
#define _MovementThread_hpp_

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class MovementThread
{
private:
	ThreadManager* parent;
	thread me;
	void run();

public:
	MovementThread(ThreadManager* _parent);
	~MovementThread();

	void launch();
	void terminate();
};

#endif // !_MovementThread_hpp_