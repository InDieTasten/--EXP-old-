#ifndef _Ship_hpp_
#define _Ship_hpp_

#include <vector>
#include <Data\PhysicalInfo.hpp>
#include <Data\GraphicalInfo.hpp>
#include <Data\Taggable.hpp>
#include <Data\PilotSeat.hpp>
#include <Data\Container.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Ship : public PhysicalInfo, public Taggable, public GraphicalInfo
{
private:
	EventManager* eventManager;
	PilotSeat seat;
	std::vector<Thruster> thrusters;
	std::vector<Container> containers;

public:
	Ship(EventManager* _eventManager);
	~Ship();

	void draw(sf::RenderTarget& target, sf::RenderStates states);

	//SET

	//MOVE
	//GET
};

#endif // !_Ship_hpp_
