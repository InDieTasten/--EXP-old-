#ifndef _Actuator_hpp_
#define _Actuator_hpp_

#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>

class Actuator
{
public:
	enum InputType
	{
		Keyboard,
		Mouse,
		Joystick
	};

private:
	InputType inputType;
	sf::Keyboard::Key key;
	sf::Joystick::Axis axis;
	bool enabled;

public:
	Actuator();
	~Actuator();

	void enable();
	void disable();
	bool getEnabled();


	void detectNext();
	void setInputType(InputType _type);
	void setKey(sf::Keyboard::Key _key);
	void setAxis(sf::Joystick::Axis _axis);

	InputType getInputType();
	sf::Keyboard::Key getKey();
	sf::Joystick::Axis getAxis();

	sf::Vector2f getControlVector();
};

#endif // !_Actuator_hpp_