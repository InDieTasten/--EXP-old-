#include <Core\EventThread.hpp>

EventThread::EventThread(sf::RenderWindow* _window)
{
	app = _window;
	looprate = 40.0f;
}
EventThread::~EventThread()
{
	app = nullptr;
}
void EventThread::run()
{

	while (app->isOpen())
	{
		sf::Event Event;
		while (app->pollEvent(Event))
		{
			//WORK do something with events
		}
	}
}