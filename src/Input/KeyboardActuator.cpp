#include <Input\KeyboardActuator.hpp>

KeyboardActuator::KeyboardActuator(EventManager* _manager) : Actuator()
{
	if (!_manager)
	{
		EXP::log("[Warning]KeyboardActuator constructed using nullptr as EventManager");
	}
	eventManager = _manager;
	EXP::log("[Info]KeyboardActuator has been constructed: " + utils::tostring(this));
}
KeyboardActuator::KeyboardActuator(EventManager* _manager, sf::Keyboard::Key _code) : Actuator()
{
	KeyboardActuator::KeyboardActuator(_manager);
	setKeyCode(_code);
}
KeyboardActuator::~KeyboardActuator()
{

	EXP::log("[Info]KeyboardActuator has been destructed: " + utils::tostring(this));
}

float KeyboardActuator::getRawVector()
{
	confmtx.lock();
	float result = sf::Keyboard::isKeyPressed(code);
	confmtx.unlock();
	return result;
}

void KeyboardActuator::listen(EventPublisher* _sender, sf::Event::KeyEvent _event)
{
	confmtx.lock();
	code = _event.code;
	eventManager->removeKeyPress(Delegate<sf::Event::KeyEvent>(this, &KeyboardActuator::listen));
	confmtx.unlock();
}

void KeyboardActuator::detectNext()
{
	eventManager->addKeyPress(Delegate<sf::Event::KeyEvent>(this, &KeyboardActuator::listen));
}

void KeyboardActuator::setKeyCode(sf::Keyboard::Key _key)
{
	confmtx.lock();
	code = _key;
	confmtx.unlock();
}
void KeyboardActuator::setEventManager(EventManager* _manager)
{
	if (!_manager)
	{
		EXP::log("[Warning]KeyboardActuators EventManager set to nullptr");
	}
	confmtx.lock();
	eventManager = _manager;
	confmtx.unlock();
}
sf::Keyboard::Key KeyboardActuator::getKeyCode()
{
	confmtx.lock();
	sf::Keyboard::Key result = code;
	confmtx.unlock();
	return result;
}
EventManager* KeyboardActuator::getEventManager()
{
	confmtx.lock();
	EventManager* result = eventManager;
	confmtx.unlock();
	return result;
}
