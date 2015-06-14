#ifndef _PilotSeat_hpp_
#define _PilotSeat_hpp_

#include <Input\EventManager.hpp>
#include <Data\Attachable.hpp>
#include <Data\Taggable.hpp>
#include <Input\Actuator.hpp>
#include <Data\Thruster.hpp>
#include <vector>


class PilotSeat : public Attachable, public Taggable
{
private:
	EventManager* eventManager;

	Actuator translateForward;
	Actuator translateBack;
	Actuator translateLeft;
	Actuator translateRight;
	Actuator rotateLeft;
	Actuator rotateRight;
	Actuator primaryWeapon;
	Actuator secondaryWeapon;
public:
	PilotSeat(EventManager* _eventManager);
	~PilotSeat();

	void setThrottle(std::vector<Thruster>& _thrusters); //will return the current input vector for the thruster given
};

#endif // !_PilotSeat_hpp_
