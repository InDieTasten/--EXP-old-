#ifndef _GraphicsThread_hpp_
#define _GraphicsThread_hpp_


using namespace std;

class GraphicsThread
{
private:
	ThreadManager* parent;
public:
	GraphicsThread();
	~GraphicsThread();
};

#endif // !_GraphicsThread_hpp_