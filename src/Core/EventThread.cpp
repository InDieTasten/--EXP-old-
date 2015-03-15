#include <Core\EventThread.hpp>
#include <Core\ThreadManager.hpp>

EventThread::EventThread(sf::RenderWindow* _window)
{
	//pointer
	app = _window;

	//init
	looptime = chrono::milliseconds(1000/50);
}
EventThread::~EventThread()
{
	app = nullptr;
}
void EventThread::run()
{
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (true)
	{
		//thread throttle
		this_thread::sleep_for(looptime - (chrono::steady_clock::now() - last));
		last = chrono::steady_clock::now();


		sf::Event Event;
		while (app->pollEvent(Event))
		{
			//WORK do something with events
			this_thread::sleep_for(chrono::seconds(10));
			return;
		}
	}
}
void EventThread::addParent(ThreadManager* _manager)
{
	for (auto it : parents)
	{
		if (it == _manager)
		{
			ug::log("[Warning]Tried to set homophobic parent to EventThread");
			return;
		}
	}
	parents.push_back(_manager);
	ug::log("[Info]A parent was added to EventThread");
}
void EventThread::removeParent(ThreadManager* _manager)
{
	for (auto it : parents)
	{
		if (it == _manager)
		{
			parents.remove(it);
			ug::log("[Info]A parent was removed from EventThread");
			return;
		}
	}
	ug::log("[Warning]Tried removing non-existant parent from EventThread");
}