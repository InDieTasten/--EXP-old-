#include <Processing\GameEngine.hpp>
#include <Utilities\VERSION.hpp>



GameEngine::GameEngine()
{
	gameWindow = nullptr;
	eventManager = nullptr;
	renderer = nullptr;
	simulator = nullptr;
	level = nullptr;

	EXP::log("[Info]GameEngine has been constructed: " + utils::tostring(this));
}
GameEngine::~GameEngine()
{
	
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

	EXP::log("[Info]GameEngine has been destructed: " + utils::tostring(this));
}

void GameEngine::launch()
{
	//Check for current instance
	if (gameWindow)
	{
		EXP::log("[Error]Tried launching already running GameEngine: " + utils::tostring(this));
		return;
	}

	EXP::log("[Info]Game is launching in version: " + VERSION::version);

	//create window
	gameWindow = new sf::RenderWindow(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	defaultView = gameWindow->getDefaultView();
	defaultView.setCenter(0.0f, 0.0f);
	gameWindow->setView(defaultView);
	gameWindow->clear(sf::Color::Black);
	gameWindow->display();

	//create event handler for that window
	eventManager = new EventManager(gameWindow);

	//Here comes the loading screen logic (WORK)
	// the main thread should just hook into that, so it requires an extra thread to launch the other threads and generate the level xD

	//default level
	level = new System();

	//threads
	renderer = new Renderer(gameWindow, level);
	simulator = new Simulator(gameWindow, level);
	renderer->launch();
	simulator->launch();

	//have the main thread listen
	eventManager->listen();

	//stopping
	simulator->terminate();
	renderer->terminate();
	delete simulator;
	simulator = nullptr;
	delete renderer;
	renderer = nullptr;

	delete level;
	level = nullptr;

	delete eventManager;
	eventManager = nullptr;

	gameWindow->close();
	delete gameWindow;
	gameWindow = nullptr;
}