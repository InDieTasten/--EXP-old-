#ifndef _Ship_hpp_
#define _Ship_hpp_

#include <list>
#include <Data\PhysicalInfo.hpp>
#include <Data\Taggable.hpp>
#include <Data\PilotSeat.hpp>


class Ship : public PhysicalInfo, public Taggable
{
private:
	void updateMass();
	PilotSeat seat;
	
public:
	Ship();
	~Ship();



	void draw(sf::RenderTarget* _target);
};

#endif // !_Ship_hpp_