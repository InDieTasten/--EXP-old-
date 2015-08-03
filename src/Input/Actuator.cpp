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
	confmtx.lock();
	float result = multiplier * getRawVector() + adjustment;
	confmtx.unlock();
	return result;
}

void Actuator::setMultiplier(float _value)
{
	confmtx.lock();
	multiplier = _value;
	confmtx.unlock();
}
void Actuator::setAdjustment(float _value)
{
	confmtx.lock();
	adjustment = _value;
	confmtx.unlock();
}
float Actuator::getMultiplier()
{
	confmtx.lock();
	float result = multiplier;
	confmtx.unlock();
	return result;
}
float Actuator::getAdjustment()
{
	confmtx.lock();
	float result = adjustment;
	confmtx.unlock();
	return result;
}
