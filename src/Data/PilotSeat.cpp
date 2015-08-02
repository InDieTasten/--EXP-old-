#include <Data\PilotSeat.hpp>

PilotSeat::PilotSeat(EventManager* _eventManager) :
Attachable(),
Taggable(),
eventManager(_eventManager),
translateForward(new NullActuator),
translateBack(new NullActuator),
translateLeft(new NullActuator),
translateRight(new NullActuator),
rotateLeft(new NullActuator),
rotateRight(new NullActuator),
primaryWeapon(new NullActuator),
secondaryWeapon(new NullActuator)
{
	EXP::log("[Info]PilotSeat has been constructed: " + utils::tostring(this));
}
PilotSeat::~PilotSeat()
{
	delete translateForward;
	delete translateBack;
	delete translateLeft;
	delete translateRight;
	delete rotateLeft;
	delete rotateRight;
	delete primaryWeapon;
	delete secondaryWeapon;
	EXP::log("[Info]PilotSeat has been destructed: " + utils::tostring(this));
}

void PilotSeat::setTranslateForward(Actuator& _act)
{
	delete translateForward;
	translateForward = &_act;
}
void PilotSeat::setTranslateBack(Actuator& _act)
{
	delete translateBack;
	translateBack = &_act;
}
void PilotSeat::setTranslateLeft(Actuator& _act)
{
	delete translateLeft;
	translateLeft = &_act;
}
void PilotSeat::setTranslateRight(Actuator& _act)
{
	delete translateRight;
	translateRight = &_act;
}
void PilotSeat::setRotateLeft(Actuator& _act)
{
	delete rotateLeft;
	rotateLeft = &_act;
}
void PilotSeat::setRotateRight(Actuator& _act)
{
	delete rotateRight;
	rotateRight = &_act;
}
void PilotSeat::setPrimaryWeapon(Actuator& _act)
{
	delete primaryWeapon;
	primaryWeapon = &_act;
}
void PilotSeat::setSecondaryWeapon(Actuator& _act)
{
	delete secondaryWeapon;
	secondaryWeapon = &_act;
}
Actuator& PilotSeat::getTranslateForward()
{
	return *translateForward;
}
Actuator& PilotSeat::getTranslateBack()
{
	return *translateBack;
}
Actuator& PilotSeat::getTranslateLeft()
{
	return *translateLeft;
}
Actuator& PilotSeat::getTranslateRight()
{
	return *translateRight;
}
Actuator& PilotSeat::getRotateLeft()
{
	return *rotateLeft;
}
Actuator& PilotSeat::getRotateRight()
{
	return *rotateRight;
}
Actuator& PilotSeat::getPrimaryWeapon()
{
	return *primaryWeapon;
}
Actuator& PilotSeat::getSecondaryWeapon()
{
	return *secondaryWeapon;
}

void PilotSeat::setThrottle(std::vector<Thruster>& _thrusters)
{
	//WORK
}
