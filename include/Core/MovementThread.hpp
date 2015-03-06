#ifndef _MovementThread_hpp_
#define _MovementThread_hpp_

class ThreadManager;

using namespace std;

class MovementThread
{
private:
	ThreadManager* parent;

public:
	MovementThread();
	~MovementThread();
};

#endif // !_MovementThread_hpp_