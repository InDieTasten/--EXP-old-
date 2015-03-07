#ifndef _GravityThread_hpp_
#define _GravityThread_hpp_

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GravityThread
{
private:
	ThreadManager* parent;

public:
	GravityThread();
	~GravityThread();
};

#endif // !_GravityThread_hpp_