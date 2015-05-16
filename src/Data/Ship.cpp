#include <Data\Ship.hpp>

Ship::Ship() : Taggable()
{
	EXP::log("[Info]Ship has been constructed: " + utils::tostring(this));
}
Ship::~Ship()
{
	EXP::log("[Info]Ship has been destructed: " +  utils::tostring(this));
}

