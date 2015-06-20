#ifndef _EventManager_hpp_
#define _EventManager_hpp_

#include <list>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <GUI\GUIManager.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class EventManager
{
private:
	//Listener Register
	//(input)
	std::list<void(*)(sf::Event::MouseMoveEvent)> mouseMove;
	std::list<void(*)(sf::Event::MouseButtonEvent)> mousePress;
	std::list<void(*)(sf::Event::MouseButtonEvent)> mouseRelease;
	std::list<void(*)(sf::Event::MouseWheelEvent)> mouseWheel;
	std::list<void(*)(sf::Event::KeyEvent)> keyPress;
	std::list<void(*)(sf::Event::KeyEvent)> keyRelease;
	std::list<void(*)(sf::Event::TextEvent)> textEnter;
	std::list<void(*)(sf::Event::JoystickButtonEvent)> joyPress;
	std::list<void(*)(sf::Event::JoystickButtonEvent)> joyRelease;
	std::list<void(*)(sf::Event::JoystickConnectEvent)> joyConnect;
	std::list<void(*)(sf::Event::JoystickConnectEvent)> joyDisconnect;
	std::list<void(*)(sf::Event::JoystickMoveEvent)> joyMove;
	//(misc)
	std::list<void(*)(void)> focusGained;
	std::list<void(*)(void)> focusLost;
	std::list<void(*)(void)> mouseEnter;
	std::list<void(*)(void)> mouseLeave;
	std::list<void(*)(sf::Event::SizeEvent)> resize;
	//(any)
	std::list<void(*)(sf::Event*)> any;

	sf::RenderWindow* target;
	bool listening;
	sf::Mutex confmtx;

public:
	EventManager(sf::RenderWindow* _target);
	~EventManager();

	void listen(GUIManager* _guiManager);
	void terminate();

	void addMouseMove(void(*_listener)(sf::Event::MouseMoveEvent));
	void removeMouseMove(void(*_listener)(sf::Event::MouseMoveEvent));
	void addMousePress(void(*_listener)(sf::Event::MouseButtonEvent));
	void removeMousePress(void(*_listener)(sf::Event::MouseButtonEvent));
	void addMouseRelease(void(*_listener)(sf::Event::MouseButtonEvent));
	void removeMouseRelease(void(*_listener)(sf::Event::MouseButtonEvent));
	void addMouseWheel(void(*_listener)(sf::Event::MouseWheelEvent));
	void removeMouseWheel(void(*_listener)(sf::Event::MouseWheelEvent));
	void addKeyPress(void(*_listener)(sf::Event::KeyEvent));
	void removeKeyPress(void(*_listener)(sf::Event::KeyEvent));
	void addKeyRelease(void(*_listener)(sf::Event::KeyEvent));
	void removeKeyRelease(void(*_listener)(sf::Event::KeyEvent));
	void addTextEnter(void(*_listener)(sf::Event::TextEvent));
	void removeTextEnter(void(*_listener)(sf::Event::TextEvent));
	void addJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent));
	void removeJoyPress(void(*_listener)(sf::Event::JoystickButtonEvent));
	void addJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent));
	void removeJoyRelease(void(*_listener)(sf::Event::JoystickButtonEvent));
	void addJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent));
	void removeJoyConnect(void(*_listener)(sf::Event::JoystickConnectEvent));
	void addJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent));
	void removeJoyDisconnect(void(*_listener)(sf::Event::JoystickConnectEvent));
	void addJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent));
	void removeJoyMove(void(*_listener)(sf::Event::JoystickMoveEvent));
	void addFocusGained(void(*_listener)(void));
	void removeFocusGained(void(*_listener)(void));
	void addFocusLost(void(*_listener)(void));
	void removeFocusLost(void(*_listener)(void));
	void addMouseEnter(void(*_listener)(void));
	void removeMouseEnter(void(*_listener)(void));
	void addMouseLeave(void(*_listener)(void));
	void removeMouseLeave(void(*_listener)(void));
	void addResize(void(*_listener)(sf::Event::SizeEvent));
	void removeResize(void(*_listener)(sf::Event::SizeEvent));
	void addAny(void(*_listener)(sf::Event*));
	void removeAny(void(*_listener)(sf::Event*));
};

#endif // !_EventManager_hpp_
