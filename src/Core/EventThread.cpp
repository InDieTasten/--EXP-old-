#include <Core\EventThread.hpp>

EventThread::EventThread(sf::RenderWindow* _window)
{
	app = _window;
}
EventThread::~EventThread()
{
	app = nullptr;
}
