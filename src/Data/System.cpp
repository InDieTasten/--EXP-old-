#include <Data\System.hpp>

System::System()
{
	EXP::log("[Info]System has been constructed: " + utils::tostring(this));
}
System::~System()
{
	EXP::log("[Info]System has been destrcted: " + utils::tostring(this));
}