#include <Core\EventThread.hpp>

EventThread::EventThread(sf::RenderWindow* _window)
{
	app = _window;
	looptime = chrono::milliseconds(1000/50);
}
EventThread::~EventThread()
{
	app = nullptr;
}
void EventThread::run()
{
	chrono::steady_clock::time_point last = chrono::steady_clock::now();
	while (app->isOpen())
	{

		//consumed time:
		this_thread::sleep_for(chrono::steady_clock::now() - last - looptime);
		last = chrono::steady_clock::now();


		sf::Event Event;
		while (app->pollEvent(Event))
		{
			//WORK do something with events
		}
	}
}