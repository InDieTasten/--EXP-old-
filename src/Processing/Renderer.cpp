#include <Processing\Renderer.hpp>

Renderer::Renderer(sf::RenderWindow* _window, GUIManager* _guiManager, System* _level) :
running(false),
thread(&Renderer::run, this)
{
	window = _window;
	guiManager = _guiManager;
	level = _level;
	EXP::log("[Info]Renderer has been  constructed: " + utils::tostring(this));
}
Renderer::~Renderer()
{

	EXP::log("[Info]Renderer has been  destructed: " + utils::tostring(this));
}

void Renderer::run()
{
	EXP::log("[Info]Renderer running in this thread: " + utils::tostring(this));
	sf::Clock limiter;
	limiter.restart();

	window->setActive(true);

	while (running)
	{
		//limiter
		sf::sleep(sf::Time(sf::milliseconds(1000.0f / 60.0f) - limiter.restart()));

		//clear frame
		window->clear(sf::Color::Black);

		//rendering of level
		//window->draw(*level);

		//rendering of gui
		window->draw(*guiManager);

		//display final frame
		window->display();
	}
	EXP::log("[Info]Renderer stops running in this thread: " + utils::tostring(this));
}

void Renderer::launch()
{
	if (!running)
	{
		EXP::log("[Info]Launching Renderer in new thread: " + utils::tostring(this));
		running = true;
		thread.launch();
	}
	else {
		EXP::log("[Warning]Tried launching already running Renderer: " + utils::tostring(this));
	}
}
void Renderer::terminate()
{
	if (running)
	{
		EXP::log("[Info]Terminating Renderer: " + utils::tostring(this));
		running = false;
		thread.wait();
		sf::sleep(sf::seconds(1));
	}
	else {
		EXP::log("[Warning]Tried terminating already terminated Renderer: " + utils::tostring(this));
	}
}
void Renderer::setWindow(sf::RenderWindow* _window)
{
	bool tmp = running;
	if (running)
	{
		EXP::log("[Info]Terminating rendering to change target window: " + utils::tostring(this));
		terminate();
	}

	window = _window;

	if (tmp){
		EXP::log("[Info]Re-launching rendering after changing target window: " + utils::tostring(this));
		launch();
	}
}
void Renderer::setLevel(System* _level)
{
	bool tmp = running;
	if (running)
	{
		EXP::log("[Info]Terminating rendering to change target level: " + utils::tostring(this));
		terminate();
	}

	level = _level;

	if (tmp){
		EXP::log("[Info]Re-launching rendering after changing target level: " + utils::tostring(this));
		launch();
	}
}
sf::RenderWindow* Renderer::getWindow()
{
	return window;
}
System* Renderer::getLevel()
{
	return level;
}
