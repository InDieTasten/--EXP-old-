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

	void launch();
	void terminate();
};

#endif // !_GraphicsThread_hpp_