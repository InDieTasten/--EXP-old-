#include <Data\Thruster.hpp>

Thruster::Thruster() : Attachable(), Taggable()
{
	EXP::log("[Info]Thruster has been constructed: " +  utils::tostring(this));
}
Thruster::~Thruster()
{
	EXP::log("[Info]Thruster has been destructed: " + utils::tostring(this));
}

void Thruster::setThrust(float _thrust)
{
	thrust = _thrust;
}
void Thruster::setFuel(ResourceType _fuel)
{
	fuel = _fuel;
}
void Thruster::setISP(float _isp)
{
	isp = _isp;
}
float Thruster::getThrust()
{
	return thrust;
}
ResourceType Thruster::getFuel()
{
	return fuel;
}
float Thruster::getISP()
{
	return isp;
}