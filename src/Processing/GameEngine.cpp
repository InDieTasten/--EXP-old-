#include <Processing\GameEngine.hpp>

GameEngine::GameEngine()
{
	gameWindow = nullptr;
	eventManager = nullptr;
	renderer = nullptr;
	simulator = nullptr;
	level = nullptr;

	EXP::log("[Info]GameEngine has been  constructed: " + utils::tostring(this));
}
GameEngine::~GameEngine()
{
	//terminate all threads (WORK)

	//De-allocate game memory (note, that this is quite the hardcore way to quit it)
	delete gameWindow;
	gameWindow = nullptr;
	delete eventManager;
	eventManager = nullptr;
	delete renderer;
	renderer = nullptr;
	delete simulator;
	simulator = nullptr;
	delete level;
	level = nullptr;

	EXP::log("[Info]GameEngine has been  destructed: " + utils::tostring(this));
}

void GameEngine::launch()
{
	//create window
	gameWindow = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	gameWindow->clear();


}
