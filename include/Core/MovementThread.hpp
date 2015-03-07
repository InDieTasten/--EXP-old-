#ifndef _MovementThread_hpp_
#define _MovementThread_hpp_

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class MovementThread
{
private:
	ThreadManager* parent;

public:
	MovementThread();
	~MovementThread();
};

#endif // !_MovementThread_hpp_