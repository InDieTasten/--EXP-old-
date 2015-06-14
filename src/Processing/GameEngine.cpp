#include <Processing\GameEngine.hpp>

GameEngine::GameEngine()
{

	EXP::log("[Info]GameEngine has been  constructed: " + utils::tostring(this));
}
GameEngine::~GameEngine()
{

	EXP::log("[Info]GameEngine has been  destructed: " + utils::tostring(this));
}
