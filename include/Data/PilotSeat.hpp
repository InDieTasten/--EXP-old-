#ifndef _PilotSeat_hpp_
#define _PilotSeat_hpp_

#include <Data\Attachable.hpp>
#include <Data\Thruster.hpp>
#include <list>

struct Actuator {};

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

	float getInput(Thruster* _thruster); //will return the current input vector for the thruster given
};

#endif // !_PilotSeat_hpp_