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
	confmtx.lock();
	for (auto it = mouseMove.begin(); it != mouseMove.end(); it++)
	{
		if (*it == _listener)
		{
			mouseMove.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MouseMove listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MouseMove listener");
}
void EventManager::addMousePress(void(*_listener)(sf::Event::MouseButtonEvent))
{
	confmtx.lock();
	mousePress.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MousePress listener registered");
}
void EventManager::removeMousePress(void(*_listener)(sf::Event::MouseButtonEvent))
{
	confmtx.lock();
	for (auto it = mousePress.begin(); it != mousePress.end(); it++)
	{
		if (*it == _listener)
		{
			mousePress.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MousePress listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MousePress listener");
}
void EventManager::addMouseRelease(void(*_listener)(sf::Event::MouseButtonEvent))
{
	confmtx.lock();
	mouseRelease.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MouseRelease listener registered");
}
void EventManager::removeMouseRelease(void(*_listener)(sf::Event::MouseButtonEvent))
{
	confmtx.lock();
	for (auto it = mouseRelease.begin(); it != mouseRelease.end(); it++)
	{
		if (*it == _listener)
		{
			mouseRelease.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MouseRelease listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MouseRelease listener");
}
void EventManager::addMouseWheel(void(*_listener)(sf::Event::MouseWheelEvent))
{
	confmtx.lock();
	mouseWheel.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MouseWheel listener registered");
}
void EventManager::removeMouseWheel(void(*_listener)(sf::Event::MouseWheelEvent))
{
	confmtx.lock();
	for (auto it = mouseWheel.begin(); it != mouseWheel.end(); it++)
	{
		if (*it == _listener)
		{
			mouseWheel.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MouseWheel listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MouseWheel listener");
}
void EventManager::addKeyPress(void(*_listener)(sf::Event::KeyEvent))
{
	confmtx.lock();
	keyPress.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]KeyPress listener registered");
}
void EventManager::removeKeyPress(void(*_listener)(sf::Event::KeyEvent))
{
	confmtx.lock();
	for (auto it = keyPress.begin(); it != keyPress.end(); it++)
	{
		if (*it == _listener)
		{
			keyPress.erase(it);
			confmtx.unlock();
			EXP::log("[Info]KeyPress listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered KeyPress listener");
}
void EventManager::addKeyRelease(void(*_listener)(sf::Event::KeyEvent)){}
void EventManager::removeKeyRelease(void(*_listener)(sf::Event::KeyEvent)){}
void EventManager::addTextEnter(void(*_listener)(sf::Event::TextEvent)){}
void EventManager::removeTextEnter(void(*_listener)(sf::Event::TextEvent)){}
void EventManager::addJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent)){}
void EventManager::removeJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent)){}
void EventManager::addJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent)){}
void EventManager::removeJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent)){}
void EventManager::addJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent)){}
void EventManager::removeJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent)){}
void EventManager::addJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent)){}
void EventManager::removeJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent)){}
void EventManager::addJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent)){}
void EventManager::removeJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent)){}
void EventManager::addFocusGained(void(*_listener)(void)){}
void EventManager::removeFocusGained(void(*_listener)(void)){}
void EventManager::addFocusLost(void(*_listener)(void)){}
void EventManager::removeFocusLost(void(*_listener)(void)){}
void EventManager::addResize(void(*_listener)(sf::Event::SizeEvent)){}
void EventManager::removeResize(void(*_listener)(sf::Event::SizeEvent)){}