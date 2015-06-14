#include <Data\Attachable.hpp>

Attachable::Attachable()
{
	EXP::log("[Info]Attachable has been constructed: " + utils::tostring(this));
}
Attachable::~Attachable()
{
	EXP::log("[Info]Attachable has been destructed: " + utils::tostring(this));
}
