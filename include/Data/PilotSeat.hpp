#ifndef _PilotSeat_hpp_
#define _PilotSeat_hpp_

#include <Data\Attachable.hpp>
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

	void calibrateThrusters(std::list<Thruster*>);
};

#endif // !_PilotSeat_hpp_