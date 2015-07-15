#include <Input\Actuator.hpp>

Actuator::Actuator()
{
	eventManager = nullptr;
	enabled = true;
	inputType = InputType::Keyboard;
	key = sf::Keyboard::Escape;
	button = sf::Mouse::Left;
	mouseAxis = MouseAxis::X;
	joystick = 0;
	joyButton = 0;
	axis = sf::Joystick::X;
	EXP::log("[Info]Actuator has been constructed: " + utils::tostring(this));
}
Actuator::Actuator(EventManager* _eventManager)
{
	eventManager = _eventManager;
	enabled = true;
	inputType = InputType::Keyboard;
	key = sf::Keyboard::Escape;
	button = sf::Mouse::Left;
	mouseAxis = MouseAxis::X;
	joystick = 0;
	joyButton = 0;
	axis = sf::Joystick::X;
	EXP::log("[Info]Actuator has been constructed: " + utils::tostring(this));
}
Actuator::~Actuator()
{
	EXP::log("[Info]Actuator has been destructed: " + utils::tostring(this));
}

bool Actuator::getEnabled()
{
	return enabled;
}
void Actuator::detectNext()
{

}
void Actuator::detectNext(InputType _filter)
{

}

void Actuator::setEventManager(EventManager* _eventManager)
{
	eventManager = _eventManager;
}
EventManager* Actuator::getEventManager()
{
	return eventManager;
}

void Actuator::setInputType(InputType _type)
{
	inputType = _type;
}
void Actuator::setKey(sf::Keyboard::Key _key)
{
	key = _key;
}
void Actuator::setButton(sf::Mouse::Button _button)
{
	button = _button;
}
void Actuator::setMouseAxis(MouseAxis _mouseAxis)
{
	mouseAxis = _mouseAxis;
}
void Actuator::setAxis(unsigned int _joystick, sf::Joystick::Axis _axis)
{
	joystick = _joystick;
	axis = _axis;
}
void Actuator::setJoyButton(unsigned int _joystick, unsigned int _button)
{
	joystick = _joystick;
	joyButton = _button;
}
Actuator::InputType Actuator::getInputType()
{
	return inputType;
}
sf::Keyboard::Key Actuator::getKey()
{
	return key;
}
sf::Mouse::Button Actuator::getButton()
{
	return button;
}
Actuator::MouseAxis Actuator::getMouseAxis()
{
	return mouseAxis;
}
sf::Joystick::Axis Actuator::getAxis()
{
	return axis;
}
unsigned int Actuator::getJoystick()
{
	return joystick;
}
unsigned int Actuator::getJoyButton()
{
	return joyButton;
}
void Actuator::setControlVector(float _value)
{
	value = _value;
}
float Actuator::getControlVector()
{
	switch (inputType)
	{
	case InputType::Magic:
		return value;
	case InputType::Keyboard:
		return (float)sf::Keyboard::isKeyPressed(key);
	case InputType::MouseButton:
		return (float)sf::Mouse::isButtonPressed(button);
	case InputType::MousePosition:
		switch (mouseAxis)
		{
		case MouseAxis::X:
			return sf::Mouse::getPosition().x;
		case MouseAxis::Y:
			return sf::Mouse::getPosition().y;
		default:
			EXP::log("[Warning]Actuators mouse axis is highly strange: " + utils::tostring(this));
			return 0.0f;
		}
	case InputType::Joystick:
		return sf::Joystick::getAxisPosition(joystick, axis) / 100.0f;
	case InputType::JoystickButton:
		return (float)sf::Joystick::isButtonPressed(joystick, joyButton);
	default:
		EXP::log("[Warning]Actuators input type is highly strange: " + utils::tostring(this));
		return 0.0f;
	}
}
