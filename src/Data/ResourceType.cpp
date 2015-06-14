#include <Data\ResourceType.hpp>

ResourceType::ResourceType() : Taggable()
{
	EXP::log("[Info]ResourceType has been constructed: " + utils::tostring(this));
}
ResourceType::~ResourceType()
{
	EXP::log("[Info]ResourceType has been destructed: " + utils::tostring(this));
}
