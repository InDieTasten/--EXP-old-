#ifndef _GraphicsThread_hpp_
#define _GraphicsThread_hpp_

#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>
#include <thread>

class ThreadManager;

using namespace std;
extern void ug::log(std::string);

class GraphicsThread
{
private:
	ThreadManager* parent;
	sf::RenderWindow* renderWindow;
	thread me;

	chrono::milliseconds looptime;
	bool running;
	void run();

public:
	GraphicsThread(sf::RenderWindow* _renderWindow);
	~GraphicsThread();

	bool isRunning();

	void launch();
	void terminate();
};

#endif // !_GraphicsThread_hpp_