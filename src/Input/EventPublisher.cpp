#include <Input\EventPublisher.hpp>

EventPublisher::EventPublisher()
{

	EXP::log("[Info]EventPublisher has been constructed: " + utils::tostring(this));
}
EventPublisher::~EventPublisher()
{

	EXP::log("[Info]EventPublisher has been destructed: " + utils::tostring(this));
}
