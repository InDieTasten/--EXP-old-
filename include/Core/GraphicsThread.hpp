#ifndef _GraphicsThread_hpp_
#define _GraphicsThread_hpp_

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GraphicsThread
{
private:
	ThreadManager* parent;
public:
	GraphicsThread();
	~GraphicsThread();
};

#endif // !_GraphicsThread_hpp_