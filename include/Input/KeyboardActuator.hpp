#ifndef _KeyboardActuator_hpp_
#define _KeyboardActuator_hpp_

#include <Input\Actuator.hpp>
#include <SFML\Graphics.hpp>
#include <Input\EventManager.hpp>

class KeyboardActuator : public Actuator
{
private:
	sf::Keyboard::Key code;
	EventManager* eventManager;

	virtual float getRawVector();
	void listen(EventPublisher*, sf::Event::KeyEvent);
public:
	KeyboardActuator(EventManager* _manager);
	~KeyboardActuator();

	void detectNext();

	void setKeyCode(sf::Keyboard::Key);
	void setEventManager(EventManager*);
	sf::Keyboard::Key getKeyCode();
	EventManager* getEventManager();
};

#endif // !_KeyboardActuator_hpp_