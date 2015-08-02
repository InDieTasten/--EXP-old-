#ifndef _NullActuator_hpp_
#define _NullActuator_hpp_

#include <Input\Actuator.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class NullActuator : public Actuator
{
private:
	virtual float getRawVector();
public:
	NullActuator();
	~NullActuator();
};

#endif // !_NullActuator_hpp_
