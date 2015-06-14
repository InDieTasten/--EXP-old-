#include <Processing\Simulator.hpp>

Simulator::Simulator()
{

	EXP::log("[Info]Simulator has been  constructed: " + utils::tostring(this));
}
Simulator::~Simulator()
{

	EXP::log("[Info]Simulator has been  destructed: " + utils::tostring(this));
}
