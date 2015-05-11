#ifndef _PilotSeat_hpp_
#define _PilotSeat_hpp_

#include <Data\Attachable.hpp>
#include <Input\Actuator.hpp>
#include <Data\Thruster.hpp>
#include <list>


class PilotSeat : public Attachable
{
private:
	Actuator translateForward;
	Actuator translateBack;
	Actuator translateLeft;
	Actuator translateRight;
	Actuator triggerPrimary;
	Actuator triggerSecondary;
	Actuator rotateLeft;
	Actuator rotateRight;
public:
	PilotSeat();
	~PilotSeat();

	void setThrust(std::list<Thruster*> _thrusters); //will return the current input vector for the thruster given
};

#endif // !_PilotSeat_hpp_