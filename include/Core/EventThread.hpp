#ifndef _EventThread_hpp_
#define _EventThread_hpp_

#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <list>
#include <chrono>
#include <thread>

using namespace std;
extern void ug::log(string);

class ThreadManager;

class EventThread
{
private:
	list<ThreadManager*> parents;
	sf::RenderWindow* app;
	chrono::milliseconds looptime;

public:
	EventThread(sf::RenderWindow* _window);
	~EventThread();

	void run();
	void terminate();

	void addParent(ThreadManager* _manager);
	void removeParent(ThreadManager* _manager);
};

#endif // !_EventThread_hpp_