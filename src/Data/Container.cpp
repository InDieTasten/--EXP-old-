#include <Data\Container.hpp>

Container::Container() : Attachable(), Taggable()
{
	EXP::log("[Info]Container has been constructed: " + utils::tostring(this));
}
Container::~Container()
{
	EXP::log("[Info]Container has been destrcuted: " + utils::tostring(this));
}
