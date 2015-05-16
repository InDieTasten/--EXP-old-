#include <Data\Taggable.hpp>

Taggable::Taggable()
{
	EXP::log("[Info]Taggable has been constructed: " + utils::tostring(this));
}
Taggable::~Taggable()
{
	EXP::log("[Info]Taggable has been destructed: " + utils::tostring(this));
}
