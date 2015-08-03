#include <Input\EventManager.hpp>

EventManager::EventManager(sf::RenderWindow& _target) :
EventPublisher(),
target(_target)
{
	listening = false;

	EXP::log("[Info]EventManager has been constructed: " + utils::tostring(this));
}
EventManager::~EventManager()
{
	if (listening)
	{
		EXP::log("[Warning]Forcefully terminating EventManager");
		terminate();
	}
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
	sf::Time time(sf::milliseconds(1000.0f/300.0f));
	while (listening)
	{
		confmtx.unlock();
		sf::sleep(time - limiter.restart());
		confmtx.lock();

		sf::Event event;


		any(this, &event);

		while (target.pollEvent(event))
		{
			target.setView(target.getDefaultView());
			_guiManager->handleEvent(target, &event);

			switch (event.type)
			{
			case sf::Event::MouseMoved:
					mouseMove(this, event.mouseMove);
				break;
			case sf::Event::MouseButtonPressed:
				mousePress(this, event.mouseButton);
				break;
			case sf::Event::MouseButtonReleased:
				mouseRelease(this, event.mouseButton);
				break;
			case sf::Event::MouseWheelMoved:
				mouseWheel(this, event.mouseWheel);
				break;
			case sf::Event::KeyPressed:
				keyPress(this, event.key);
				break;
			case sf::Event::KeyReleased:
				keyRelease(this, event.key);
				break;
			case sf::Event::TextEntered:
				textEnter(this, event.text);
				break;
			case sf::Event::JoystickButtonPressed:
				joyPress(this, event.joystickButton);
				break;
			case sf::Event::JoystickButtonReleased:
				joyRelease(this, event.joystickButton);
				break;
			case sf::Event::JoystickConnected:
				joyConnect(this, event.joystickConnect);
				break;
			case sf::Event::JoystickDisconnected:
				joyDisconnect(this, event.joystickConnect);
				break;
			case sf::Event::JoystickMoved:
				joyMove(this, event.joystickMove);
				break;
			case sf::Event::GainedFocus:
				focusGained(this, EventArgs());
				break;
			case sf::Event::LostFocus:
				focusLost(this, EventArgs());
				break;
			case sf::Event::MouseEntered:
				mouseEnter(this, EventArgs());
				break;
			case sf::Event::MouseLeft:
				mouseLeave(this, EventArgs());
				break;
			case sf::Event::Resized:
				resize(this, event.size);
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

void EventManager::addMouseMove(Delegate<sf::Event::MouseMoveEvent> _delegate)
{
	mouseMove += _delegate;
	EXP::log("[Info]MouseMove listener registered");
}
void EventManager::removeMouseMove(Delegate<sf::Event::MouseMoveEvent> _delegate)
{
	mouseMove -= _delegate;
	EXP::log("[Info]MouseMove listener unregisterd");
}
void EventManager::addMousePress(Delegate<sf::Event::MouseButtonEvent> _delegate)
{
	mousePress += _delegate;
	EXP::log("[Info]MousePress listener registered");
}
void EventManager::removeMousePress(Delegate<sf::Event::MouseButtonEvent> _delegate)
{
	mousePress -= _delegate;
	EXP::log("[Info]MousePress listener unregistered");
}
void EventManager::addMouseRelease(Delegate<sf::Event::MouseButtonEvent> _delegate)
{
	mouseRelease += _delegate;
	EXP::log("[Info]MouseRelease listener registered");
}
void EventManager::removeMouseRelease(Delegate<sf::Event::MouseButtonEvent> _delegate)
{
	mouseRelease -= _delegate;
}
void EventManager::addMouseWheel(Delegate<sf::Event::MouseWheelEvent> _delegate)
{
	mouseWheel += _delegate;
	EXP::log("[Info]MouseWheel listener registered");
}
void EventManager::removeMouseWheel(Delegate<sf::Event::MouseWheelEvent> _delegate)
{
	mouseWheel -= _delegate;
}
void EventManager::addKeyPress(Delegate<sf::Event::KeyEvent> _delegate)
{
	keyPress += _delegate;
	EXP::log("[Info]KeyPress listener registered");
}
void EventManager::removeKeyPress(Delegate<sf::Event::KeyEvent> _delegate)
{
	keyPress -= _delegate;
}
void EventManager::addKeyRelease(Delegate<sf::Event::KeyEvent> _delegate)
{
	keyRelease += _delegate;
	EXP::log("[Info]KeyRelease listener registered");
}
void EventManager::removeKeyRelease(Delegate<sf::Event::KeyEvent> _delegate)
{
	keyRelease -= _delegate;
}
void EventManager::addTextEnter(Delegate<sf::Event::TextEvent> _delegate)
{
	textEnter += _delegate;
	EXP::log("[Info]TextEnter listener registered");
}
void EventManager::removeTextEnter(Delegate<sf::Event::TextEvent> _delegate)
{
	textEnter -= _delegate;
}
void EventManager::addJoyPress(Delegate<sf::Event::JoystickButtonEvent> _delegate)
{
	joyPress += _delegate;
	EXP::log("[Info]JoyPress listener registered");
}
void EventManager::removeJoyPress(Delegate<sf::Event::JoystickButtonEvent> _delegate)
{
	joyPress -= _delegate;
}
void EventManager::addJoyRelease(Delegate<sf::Event::JoystickButtonEvent> _delegate)
{
	joyRelease += _delegate;
	EXP::log("[Info]JoyRelease listener registered");
}
void EventManager::removeJoyRelease(Delegate<sf::Event::JoystickButtonEvent> _delegate)
{
	joyRelease -= _delegate;
}
void EventManager::addJoyConnect(Delegate<sf::Event::JoystickConnectEvent> _delegate)
{
	joyConnect += _delegate;
	EXP::log("[Info]JoyConnect listener registered");
}
void EventManager::removeJoyConnect(Delegate<sf::Event::JoystickConnectEvent> _delegate)
{
	joyConnect -= _delegate;
}
void EventManager::addJoyDisconnect(Delegate<sf::Event::JoystickConnectEvent> _delegate)
{
	joyDisconnect += _delegate;
	EXP::log("[Info]JoyDisconnect listener registered");
}
void EventManager::removeJoyDisconnect(Delegate<sf::Event::JoystickConnectEvent> _delegate)
{
	joyDisconnect -= _delegate;
}
void EventManager::addJoyMove(Delegate<sf::Event::JoystickMoveEvent> _delegate)
{
	joyMove += _delegate;
	EXP::log("[Info]JoyMove listener registered");
}
void EventManager::removeJoyMove(Delegate<sf::Event::JoystickMoveEvent> _delegate)
{
	joyMove -= _delegate;
}
void EventManager::addFocusGained(Delegate<EventArgs> _delegate)
{
	focusGained += _delegate;
	EXP::log("[Info]FocusGained listener registered");
}
void EventManager::removeFocusGained(Delegate<EventArgs> _delegate)
{
	focusGained -= _delegate;
}
void EventManager::addFocusLost(Delegate<EventArgs> _delegate)
{
	focusLost += _delegate;
	EXP::log("[Info]FocusLost listener registered");
}
void EventManager::removeFocusLost(Delegate<EventArgs> _delegate)
{
	focusLost -= _delegate;
}
void EventManager::addMouseEnter(Delegate<EventArgs> _delegate)
{
	mouseEnter += _delegate;
	EXP::log("[Info]MouseEnter listener registered");
}
void EventManager::removeMouseEnter(Delegate<EventArgs> _delegate)
{
	mouseEnter -= _delegate;
}
void EventManager::addMouseLeave(Delegate<EventArgs> _delegate)
{
	mouseLeave += _delegate;
	EXP::log("[Info]MouseLeave listener registered");
}
void EventManager::removeMouseLeave(Delegate<EventArgs> _delegate)
{
	mouseLeave -= _delegate;
}
void EventManager::addResize(Delegate<sf::Event::SizeEvent> _delegate)
{
	resize += _delegate;
	EXP::log("[Info]Resize listener registered");
}
void EventManager::removeResize(Delegate<sf::Event::SizeEvent> _delegate)
{
	resize -= _delegate;
}
void EventManager::addAny(Delegate<sf::Event*> _delegate)
{
	any += _delegate;
	EXP::log("[Info]Any listener registered");
}
void EventManager::removeAny(Delegate<sf::Event*> _delegate)
{
	any -= _delegate;
}
