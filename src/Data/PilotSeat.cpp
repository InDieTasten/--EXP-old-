#include <Data\PilotSeat.hpp>

PilotSeat::PilotSeat() : Attachable(), Taggable()
{
	EXP::log("[Info]PilotSeat has been constructed: " + utils::tostring(this));
}
PilotSeat::~PilotSeat()
{
	EXP::log("[Info]PilotSeat has been destructed: " + utils::tostring(this));
}