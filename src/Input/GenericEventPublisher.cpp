#include <Input\GenericEventPublisher.hpp>

GenericEventPublisher::GenericEventPublisher() : EventPublisher()
{

	EXP::log("[Info]GenericEventPublisher has been constructed: " + utils::tostring(this));
}
GenericEventPublisher::~GenericEventPublisher()
{

	EXP::log("[Info]GenericEventPublisher has been destructed: " + utils::tostring(this));
}

std::string GenericEventPublisher::who()
{
	return "Generic";
}
