#include <Data\Ship.hpp>

Ship::Ship(EventManager* _eventManager) : Taggable(), seat(_eventManager)
{
	eventManager = _eventManager;
	EXP::log("[Info]Ship has been constructed: " + utils::tostring(this));
}
Ship::~Ship()
{
	EXP::log("[Info]Ship has been destructed: " + utils::tostring(this));
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	//WORK
}
