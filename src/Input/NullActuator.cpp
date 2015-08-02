#include <Input\NullActuator.hpp>

NullActuator::NullActuator() : Actuator()
{
	EXP::log("[Info]NullActuator has been constructed: " + utils::tostring(this));
}
NullActuator::~NullActuator()
{
	EXP::log("[Info]NullActuator has been destructed: " + utils::tostring(this));
}

float NullActuator::getRawVector()
{
	return 0.0f;
}
