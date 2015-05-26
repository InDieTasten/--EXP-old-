#ifndef _Actuator_hpp_
#define _Actuator_hpp_

#include <Input\EventManager.hpp>
#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Actuator
{
public:
	enum InputType
	{
		Keyboard,
		MouseButton,
		MousePosition,
		Joystick,
		JoystickButton
	};
	enum MouseAxis
	{
		X,
		Y
	};
private:
	EventManager* eventManager;

	InputType inputType;

	sf::Keyboard::Key key;
	sf::Mouse::Button button;
	MouseAxis mouseAxis;
	unsigned int joystick;
	unsigned int joyButton;
	sf::Joystick::Axis axis;

	bool enabled;

public:
	Actuator(EventManager* _eventManager);
	~Actuator();

	bool getEnabled();


	void detectNext();
	void detectNext(InputType _filter);

	void setInputType(InputType _type);
	void setKey(sf::Keyboard::Key _key);
	void setButton(sf::Mouse::Button _button);
	void setMouseAxis(MouseAxis _mouseAxis);
	void setAxis(unsigned int _joystick, sf::Joystick::Axis _axis);
	void setJoyButton(unsigned int _joystick, unsigned int _button);

	InputType getInputType();
	sf::Keyboard::Key getKey();
	sf::Mouse::Button getButton();
	MouseAxis getMouseAxis();
	sf::Joystick::Axis getAxis();
	unsigned int getJoystick();
	unsigned int getJoyButton();

	float getControlVector();
};

#endif // !_Actuator_hpp_