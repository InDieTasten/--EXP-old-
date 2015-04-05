#include <Input\EventManager.hpp>

EventManager::EventManager(sf::RenderWindow* _target)
{
	target = _target;
	listening = false;
	sampleRate = sf::milliseconds(1000/30);

	EXP::log("[Info]EventManager has been constructed");
}
EventManager::~EventManager()
{
	if (listening)
	{
		EXP::log("[Warning]Forcefully terminating EventManager");
		terminate();
	}
	target = nullptr;
	EXP::log("[Info]Forcefully disconnecting listeners");
	mouseMove.clear();
	mousePress.clear();
	mouseRelease.clear();
	mouseWheel.clear();
	keyPress.clear();
	keyRelease.clear();
	textEnter.clear();
	joyPress.clear();
	joyRelease.clear();
	joyConnect.clear();
	joyDisconnect.clear();
	joyMove.clear();
	focusGained.clear();
	focusLost.clear();
	resize.clear();

	EXP::log("[Info]EventManager has been destructed");
}
void EventManager::listen()
{
	EXP::log("[Info]EventManager starts listening");
	confmtx.lock();
	listening = true;
	sf::Clock limiter;
	limiter.restart();
	while (listening)
	{
		sf::Time time = sampleRate - limiter.restart();
		confmtx.unlock();
		sf::sleep(time);
		confmtx.lock();

		sf::Event event;
		while (target->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseMoved:
				for (auto it : mouseMove)
					it(event.mouseMove);
				break;
			case sf::Event::MouseButtonPressed:
				for (auto it : mousePress)
					it(event.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				for (auto it : mouseRelease)
					it(event.mouseButton);
				break;
			case sf::Event::MouseWheelMoved:
				for (auto it : mouseWheel)
					it(event.mouseWheel);
				break;
			case sf::Event::KeyPressed:
				for (auto it : keyPress)
					it(event.key);
				break;
			case sf::Event::KeyReleased:
				for (auto it : keyRelease)
					it(event.key);
				break;
			case sf::Event::TextEntered:
				for (auto it : textEnter)
					it(event.text);
				break;
			case sf::Event::JoystickButtonPressed:
				for (auto it : joyPress)
					it(event.joystickButton);
				break;
			case sf::Event::JoystickButtonReleased:
				for (auto it : joyRelease)
					it(event.joystickButton);
				break;
			case sf::Event::JoystickConnected:
				for (auto it : joyConnect)
					it(event.joystickConnect);
				break;
			case sf::Event::JoystickDisconnected:
				for (auto it : joyDisconnect)
					it(event.joystickConnect);
				break;
			case sf::Event::JoystickMoved:
				for (auto it : joyMove)
					it(event.joystickMove);
				break;
			case sf::Event::GainedFocus:
				for (auto it : focusGained)
					it();
				break;
			case sf::Event::LostFocus:
				for (auto it : focusLost)
					it();
				break;
			case sf::Event::Resized:
				for (auto it : resize)
					it(event.size);
				break;
			default:
				EXP::log("[WARNING]Something strange happened");
			}
		}
	}
	EXP::log("[Info]EventManager stopped listening");
	confmtx.unlock();
}
void EventManager::terminate()
{
	if (!listening)
	{
		EXP::log("[Warning]Tried terminating already terminated EventManager");
		return;
	}
	confmtx.lock();
	listening = false;
	confmtx.unlock();
}
void EventManager::setSampleRate(sf::Time _looptime)
{
	confmtx.lock();
	sampleRate = _looptime;
	confmtx.unlock();
}

void EventManager::addMouseMove(void(*_listener)(sf::Event::MouseMoveEvent))
{
	confmtx.lock();
	mouseMove.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MouseMove listener registered");
}
void EventManager::removeMouseMove(void(*_listener)(sf::Event::MouseMoveEvent))
{
	for (auto it = mouseMove.begin(); it != mouseMove.end(); it++)
	{
		if (*it == _listener)
		{
			mouseMove.erase(it);
			EXP::log("[Info]MouseMove listener removed");
			return;
		}
	}
	EXP::log("[Warning]Tried removing non-registered MouseMove listener");
}