#include <Input\Actuator.hpp>

Actuator::Actuator()
{
	multiplier = 1.0f;
	adjustment = 0.0f;
	EXP::log("[Info]Actuator has been constructed: " + utils::tostring(this));
}
Actuator::~Actuator()
{
	EXP::log("[Info]Actuator has been destructed: " + utils::tostring(this));
}

float Actuator::getControlVector()
{
	return multiplier * getRawVector() + adjustment;
}

void Actuator::setMultiplier(float _value)
{
	multiplier = _value;
}
void Actuator::setAdjustment(float _value)
{
	adjustment = _value;
}
float Actuator::getMultiplier()
{
	return multiplier;
}
float Actuator::getAdjustment()
{
	return adjustment;
}
