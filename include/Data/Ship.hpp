#ifndef _Ship_hpp_
#define _Ship_hpp_

#include <list>
#include <Data\PhysicalInfo.hpp>
#include <Data\PilotSeat.hpp>


class Ship : public PhysicalInfo
{
private:
	void recalcMass();
	PilotSeat seat;
	
public:
	Ship();
	~Ship();

	void draw(sf::RenderTarget* _target);
};

#endif // !_Ship_hpp_