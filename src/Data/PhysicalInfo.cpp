#include <Data\PhysicalInfo.hpp>

PhysicalInfo::PhysicalInfo()
{
	EXP::log("[Info]PhysicalInfo has been constructed: " + utils::tostring(this));
}
PhysicalInfo::~PhysicalInfo()
{
	EXP::log("[Info]PhysicalInfo has been destructed: " + utils::tostring(this));
}
