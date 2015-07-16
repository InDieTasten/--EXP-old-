#ifndef _Actuator_hpp_
#define _Actuator_hpp_

#include <Input\EventManager.hpp>
#include <SFML\Graphics.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>


class Actuator
{
public:
	Actuator();
	~Actuator();

	virtual float getControlVector() = 0;
};



#endif // !_Actuator_hpp_
