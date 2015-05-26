#include <Data\PilotSeat.hpp>

PilotSeat::PilotSeat(EventManager* _eventManager) : Attachable(), Taggable()
{
	eventManager = _eventManager;
	translateForward.setInputType(Actuator::InputType::Keyboard);
	translateForward.setKey(sf::Keyboard::W);
	translateBack.setInputType(Actuator::InputType::Keyboard);
	translateBack.setKey(sf::Keyboard::S);
	translateLeft.setInputType(Actuator::InputType::Keyboard);
	translateLeft.setKey(sf::Keyboard::A);
	translateRight.setInputType(Actuator::InputType::Keyboard);
	translateRight.setKey(sf::Keyboard::D);
	rotateLeft.setInputType(Actuator::InputType::Keyboard);
	rotateLeft.setKey(sf::Keyboard::Q);
	rotateRight.setInputType(Actuator::InputType::Keyboard);
	rotateRight.setKey(sf::Keyboard::E);
	EXP::log("[Info]PilotSeat has been constructed: " + utils::tostring(this));
}
PilotSeat::~PilotSeat()
{
	EXP::log("[Info]PilotSeat has been destructed: " + utils::tostring(this));
}