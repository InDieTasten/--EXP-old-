#include <Input\Actuator.hpp>

Actuator::Actuator()
{
	enabled = true;
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
	//WORK
}
void Actuator::detectNext(InputType _filter)
{
	//WORK
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
float Actuator::getControlVector()
{
	switch (inputType)
	{
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
			EXP::log("[Warning]Actuators mouse axis is highly strange: " +  utils::tostring(this));
			return 0.0f;
		}
	case InputType::Joystick:
		return sf::Joystick::getAxisPosition(joystick, axis)/100.0f;
	default:
		EXP::log("[Warning]Actuators input type is highly strange: " + utils::tostring(this));
		return 0.0f;
	}
}
