#include <Input\EventManager.hpp>

EventManager::EventManager(sf::RenderWindow* _target)
{
	target = _target;
	listening = false;
	sampleRate = sf::milliseconds(1000 / 30);

	EXP::log("[Info]EventManager has been constructed: " + utils::tostring(this));
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
	mouseEnter.clear();
	mouseLeave.clear();
	resize.clear();
	any.clear();

	EXP::log("[Info]EventManager has been destructed: " + utils::tostring(this));
}
void EventManager::listen(GUIManager* _guiManager)
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

		for (auto it : any)
		{
			it(&event);
		}

		while (target->pollEvent(event))
		{
			_guiManager->handleEvent(*target, &event);

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
			case sf::Event::MouseEntered:
				for (auto it : mouseEnter)
					it();
				break;
			case sf::Event::MouseLeft:
				for (auto it : mouseLeave)
					it();
				break;
			case sf::Event::Resized:
				for (auto it : resize)
					it(event.size);
				break;
			case sf::Event::Closed:
				EXP::log("[Info]The application is requested to close itself...");
				EXP::log("[Info]EventManager follows this request: " + utils::tostring(this));
				terminate();
				break;
			default:
				std::cout << event.type << std::endl;
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
	sf::sleep(sf::seconds(0.05f));
	confmtx.lock();
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
void EventManager::addKeyRelease(void(*_listener)(sf::Event::KeyEvent))
{
	confmtx.lock();
	keyRelease.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]KeyRelease listener registered");
}
void EventManager::removeKeyRelease(void(*_listener)(sf::Event::KeyEvent))
{
	confmtx.lock();
	for (auto it = keyRelease.begin(); it != keyRelease.end(); it++)
	{
		if (*it == _listener)
		{
			keyRelease.erase(it);
			confmtx.unlock();
			EXP::log("[Info]KeyRelease listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered KeyRelease listener");
}
void EventManager::addTextEnter(void(*_listener)(sf::Event::TextEvent))
{
	confmtx.lock();
	textEnter.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]TextEnter listener registered");
}
void EventManager::removeTextEnter(void(*_listener)(sf::Event::TextEvent))
{
	confmtx.lock();
	for (auto it = textEnter.begin(); it != textEnter.end(); it++)
	{
		if (*it == _listener)
		{
			textEnter.erase(it);
			confmtx.unlock();
			EXP::log("[Info]TextEnter listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered TextEnter listener");
}
void EventManager::addJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent))
{
	confmtx.lock();
	joyPress.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]JoyPress listener registered");
}
void EventManager::removeJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent))
{
	confmtx.lock();
	for (auto it = joyPress.begin(); it != joyPress.end(); it++)
	{
		if (*it == _listener)
		{
			joyPress.erase(it);
			confmtx.unlock();
			EXP::log("[Info]JoyPress listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered JoyPress listener");
}
void EventManager::addJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent))
{
	confmtx.lock();
	joyRelease.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]JoyRelease listener registered");
}
void EventManager::removeJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent))
{
	confmtx.lock();
	for (auto it = joyRelease.begin(); it != joyRelease.end(); it++)
	{
		if (*it == _listener)
		{
			joyRelease.erase(it);
			confmtx.unlock();
			EXP::log("[Info]JoyRelease listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered JoyRelease listener");
}
void EventManager::addJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent))
{
	confmtx.lock();
	joyConnect.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]JoyConnect listener registered");
}
void EventManager::removeJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent))
{
	confmtx.lock();
	for (auto it = joyConnect.begin(); it != joyConnect.end(); it++)
	{
		if (*it == _listener)
		{
			joyConnect.erase(it);
			confmtx.unlock();
			EXP::log("[Info]JoyConnect listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered JoyConnect listener");
}
void EventManager::addJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent))
{
	confmtx.lock();
	joyDisconnect.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]JoyDisconnect listener registered");
}
void EventManager::removeJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent))
{
	confmtx.lock();
	for (auto it = joyDisconnect.begin(); it != joyDisconnect.end(); it++)
	{
		if (*it == _listener)
		{
			joyDisconnect.erase(it);
			confmtx.unlock();
			EXP::log("[Info]JoyDisconnect listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered JoyDisconnect listener");
}
void EventManager::addJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent))
{
	confmtx.lock();
	joyMove.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]JoyMove listener registered");
}
void EventManager::removeJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent))
{
	confmtx.lock();
	for (auto it = joyMove.begin(); it != joyMove.end(); it++)
	{
		if (*it == _listener)
		{
			joyMove.erase(it);
			confmtx.unlock();
			EXP::log("[Info]JoyMove listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered JoyMove listener");
}
void EventManager::addFocusGained(void(*_listener)(void))
{
	confmtx.lock();
	focusGained.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]FocusGained listener registered");
}
void EventManager::removeFocusGained(void(*_listener)(void))
{
	confmtx.lock();
	for (auto it = focusGained.begin(); it != focusGained.end(); it++)
	{
		if (*it == _listener)
		{
			focusGained.erase(it);
			confmtx.unlock();
			EXP::log("[Info]FocusGained listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered FocusGained listener");
}
void EventManager::addFocusLost(void(*_listener)(void))
{
	confmtx.lock();
	focusLost.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]FocusLost listener registered");
}
void EventManager::removeFocusLost(void(*_listener)(void))
{
	confmtx.lock();
	for (auto it = focusLost.begin(); it != focusLost.end(); it++)
	{
		if (*it == _listener)
		{
			focusLost.erase(it);
			confmtx.unlock();
			EXP::log("[Info]FocusLost listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered FocusLost listener");
}
void EventManager::addMouseEnter(void(*_listener)(void))
{
	confmtx.lock();
	mouseEnter.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MouseEnter listener registered");
}
void EventManager::removeMouseEnter(void(*_listener)(void))
{
	confmtx.lock();
	for (auto it = mouseEnter.begin(); it != mouseEnter.end(); it++)
	{
		if (*it == _listener)
		{
			mouseEnter.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MouseEnter listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MouseEnter listener");
}
void EventManager::addMouseLeave(void(*_listener)(void))
{
	confmtx.lock();
	mouseLeave.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]MouseLeave listener registered");
}
void EventManager::removeMouseLeave(void(*_listener)(void))
{
	confmtx.lock();
	for (auto it = mouseLeave.begin(); it != mouseLeave.end(); it++)
	{
		if (*it == _listener)
		{
			mouseLeave.erase(it);
			confmtx.unlock();
			EXP::log("[Info]MouseLeave listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered MouseLeave listener");
}
void EventManager::addResize(void(*_listener)(sf::Event::SizeEvent))
{
	confmtx.lock();
	resize.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]Resize listener registered");
}
void EventManager::removeResize(void(*_listener)(sf::Event::SizeEvent))
{
	confmtx.lock();
	for (auto it = resize.begin(); it != resize.end(); it++)
	{
		if (*it == _listener)
		{
			resize.erase(it);
			confmtx.unlock();
			EXP::log("[Info]Resize listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered Resize listener");
}
void EventManager::addAny(void(*_listener)(sf::Event*))
{
	confmtx.lock();
	any.push_back(_listener);
	confmtx.unlock();
	EXP::log("[Info]Any listener registered");
}
void EventManager::removeAny(void(*_listener)(sf::Event*))
{
	confmtx.lock();
	for (auto it = any.begin(); it != any.end(); it++)
	{
		if (*it == _listener)
		{
			any.erase(it);
			confmtx.unlock();
			EXP::log("[Info]Any listener removed");
			return;
		}
	}
	confmtx.unlock();
	EXP::log("[Warning]Tried removing non-registered Any listener");
}
