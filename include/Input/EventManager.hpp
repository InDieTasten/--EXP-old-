#ifndef _EventManager_hpp_
#define _EventManager_hpp_

#include <list>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <GUI\GUIManager.hpp>
#include <Input\EventPublisher.hpp>
#include <Input\EventHandler.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class EventArgs{};

class EventManager : public EventPublisher
{
private:
	//Listener Register
	//(input)
	EventHandler<sf::Event::MouseMoveEvent> mouseMove;
	EventHandler<sf::Event::MouseButtonEvent> mousePress;
	EventHandler<sf::Event::MouseButtonEvent> mouseRelease;
	EventHandler<sf::Event::MouseWheelEvent> mouseWheel;
	EventHandler<sf::Event::KeyEvent> keyPress;
	EventHandler<sf::Event::KeyEvent> keyRelease;
	EventHandler<sf::Event::TextEvent> textEnter;
	EventHandler<sf::Event::JoystickButtonEvent> joyPress;
	EventHandler<sf::Event::JoystickButtonEvent> joyRelease;
	EventHandler<sf::Event::JoystickConnectEvent> joyConnect;
	EventHandler<sf::Event::JoystickConnectEvent> joyDisconnect;
	EventHandler<sf::Event::JoystickMoveEvent> joyMove;
	//(misc)
	EventHandler<EventArgs> focusGained;
	EventHandler<EventArgs> focusLost;
	EventHandler<EventArgs> mouseEnter;
	EventHandler<EventArgs> mouseLeave;
	EventHandler<sf::Event::SizeEvent> resize;
	//(any)
	EventHandler<sf::Event*> any;

	sf::RenderWindow* target;
	bool listening;
	sf::Mutex confmtx;

public:
	EventManager(sf::RenderWindow* _target);
	~EventManager();

	void listen(GUIManager* _guiManager);
	void terminate();

	void addMouseMove(Delegate<sf::Event::MouseMoveEvent>);
	void removeMouseMove(Delegate<sf::Event::MouseMoveEvent>);
	void addMousePress(Delegate<sf::Event::MouseButtonEvent>);
	void removeMousePress(Delegate<sf::Event::MouseButtonEvent>);
	void addMouseRelease(Delegate<sf::Event::MouseButtonEvent>);
	void removeMouseRelease(Delegate<sf::Event::MouseButtonEvent>);
	void addMouseWheel(Delegate<sf::Event::MouseWheelEvent>);
	void removeMouseWheel(Delegate<sf::Event::MouseWheelEvent>);
	void addKeyPress(Delegate<sf::Event::KeyEvent>);
	void removeKeyPress(Delegate<sf::Event::KeyEvent>);
	void addKeyRelease(Delegate<sf::Event::KeyEvent>);
	void removeKeyRelease(Delegate<sf::Event::KeyEvent>);
	void addTextEnter(Delegate<sf::Event::TextEvent>);
	void removeTextEnter(Delegate<sf::Event::TextEvent>);
	void addJoyPress(Delegate<sf::Event::JoystickButtonEvent>);
	void removeJoyPress(Delegate<sf::Event::JoystickButtonEvent>);
	void addJoyRelease(Delegate<sf::Event::JoystickButtonEvent>);
	void removeJoyRelease(Delegate<sf::Event::JoystickButtonEvent>);
	void addJoyConnect(Delegate<sf::Event::JoystickConnectEvent>);
	void removeJoyConnect(Delegate<sf::Event::JoystickConnectEvent>);
	void addJoyDisconnect(Delegate<sf::Event::JoystickConnectEvent>);
	void removeJoyDisconnect(Delegate<sf::Event::JoystickConnectEvent>);
	void addJoyMove(Delegate<sf::Event::JoystickMoveEvent>);
	void removeJoyMove(Delegate<sf::Event::JoystickMoveEvent>);
	void addFocusGained(Delegate<EventArgs>);
	void removeFocusGained(Delegate<EventArgs>);
	void addFocusLost(Delegate<EventArgs>);
	void removeFocusLost(Delegate<EventArgs>);
	void addMouseEnter(Delegate<EventArgs>);
	void removeMouseEnter(Delegate<EventArgs>);
	void addMouseLeave(Delegate<EventArgs>);
	void removeMouseLeave(Delegate<EventArgs>);
	void addResize(Delegate<sf::Event::SizeEvent>);
	void removeResize(Delegate<sf::Event::SizeEvent>);
	void addAny(Delegate<sf::Event*>);
	void removeAny(Delegate<sf::Event*>);
};

#endif // !_EventManager_hpp_
