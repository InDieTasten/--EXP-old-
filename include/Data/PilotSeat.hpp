#ifndef _PilotSeat_hpp_
#define _PilotSeat_hpp_

#include <Input\EventManager.hpp>
#include <Data\Attachable.hpp>
#include <Data\Taggable.hpp>
#include <Input\Actuator.hpp>
#include <Input\NullActuator.hpp>
#include <Data\Thruster.hpp>
#include <vector>


class PilotSeat : public Attachable, public Taggable
{
private:
	EventManager* eventManager;

	Actuator* translateForward;
	Actuator* translateBack;
	Actuator* translateLeft;
	Actuator* translateRight;
	Actuator* rotateLeft;
	Actuator* rotateRight;
	Actuator* primaryWeapon;
	Actuator* secondaryWeapon;
public:
	PilotSeat(EventManager* _eventManager);
	~PilotSeat();

	void setTranslateForward(Actuator& _act);
	void setTranslateBack(Actuator& _act);
	void setTranslateLeft(Actuator& _act);
	void setTranslateRight(Actuator& _act);
	void setRotateLeft(Actuator& _act);
	void setRotateRight(Actuator& _act);
	void setPrimaryWeapon(Actuator& _act);
	void setSecondaryWeapon(Actuator& _act);
	Actuator& getTranslateForward();
	Actuator& getTranslateBack();
	Actuator& getTranslateLeft();
	Actuator& getTranslateRight();
	Actuator& getRotateLeft();
	Actuator& getRotateRight();
	Actuator& getPrimaryWeapon();
	Actuator& getSecondaryWeapon();

	void setThrottle(std::vector<Thruster>& _thrusters); //will return the current input vector for the thruster given
};

#endif // !_PilotSeat_hpp_
