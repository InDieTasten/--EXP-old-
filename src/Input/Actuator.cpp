#include <Input\Actuator.hpp>

namespace ActDetection {
	sf::Mutex detection;
	Actuator* detecting;
	Actuator::InputType* filter;
}

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

void Actuator::getNextAny(sf::Event* _event)
{
	if (ActDetection::detecting)
	{
		if (_event->type == sf::Event::KeyPressed)
		{
			if (ActDetection::filter)
			{
				if (*ActDetection::filter != InputType::Keyboard)
					return;
				else
					delete ActDetection::filter;
				ActDetection::filter = nullptr;
			}
			ActDetection::detecting->setInputType(InputType::Keyboard);
			ActDetection::detecting->setKey(_event->key.code);
			ActDetection::detecting->eventManager->removeAny(Actuator::getNextAny);
			ActDetection::detecting = nullptr;
			ActDetection::detection.unlock();
		}
		if (_event->type == sf::Event::MouseButtonPressed)
		{
			if (ActDetection::filter)
			{
				if (*ActDetection::filter != InputType::MouseButton)
					return;
				else
					delete ActDetection::filter;
				ActDetection::filter = nullptr;
			}
			ActDetection::detecting->setInputType(InputType::MouseButton);
			ActDetection::detecting->setButton(_event->mouseButton.button);
			ActDetection::detecting->eventManager->removeAny(Actuator::getNextAny);
			ActDetection::detecting = nullptr;
			ActDetection::detection.unlock();
		}
		if (_event->type == sf::Event::JoystickButtonPressed)
		{
			if (ActDetection::filter)
			{
				if (*ActDetection::filter != InputType::JoystickButton)
					return;
				else
					delete ActDetection::filter;
				ActDetection::filter = nullptr;
			}
			ActDetection::detecting->setInputType(InputType::JoystickButton);
			ActDetection::detecting->setJoyButton(_event->joystickButton.joystickId,
				_event->joystickButton.button);
			ActDetection::detecting->eventManager->removeAny(Actuator::getNextAny);
			ActDetection::detecting = nullptr;
			ActDetection::detection.unlock();
		}
		if (_event->type == sf::Event::JoystickMoved)
		{
			if (ActDetection::filter)
			{
				if (*ActDetection::filter != InputType::Joystick)
					return;
				else
					delete ActDetection::filter;
				ActDetection::filter = nullptr;
			}
			ActDetection::detecting->setInputType(InputType::Joystick);
			ActDetection::detecting->setAxis(_event->joystickMove.joystickId,
				_event->joystickMove.axis);
			ActDetection::detecting->eventManager->removeAny(Actuator::getNextAny);
			ActDetection::detecting = nullptr;
			ActDetection::detection.unlock();
		}
	}
}

bool Actuator::getEnabled()
{
	return enabled;
}
void Actuator::detectNext()
{
	ActDetection::detection.lock();
	EXP::log("[Info]Actuator detects: " + utils::tostring(this));
	ActDetection::detecting = this;
	ActDetection::filter = nullptr;
	eventManager->addAny(Actuator::getNextAny);
}
void Actuator::detectNext(InputType _filter)
{
	ActDetection::detection.lock();
	EXP::log("[Info]Actuator detects filtered: " + utils::tostring(this));
	ActDetection::detecting = this;
	ActDetection::filter = new InputType(_filter);
	eventManager->addAny(Actuator::getNextAny);
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
