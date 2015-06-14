#include <Processing\Renderer.hpp>

Renderer::Renderer(sf::RenderWindow* _window, System* _level)
{
	window = _window;
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
	while (running)
	{
		//limiter
		//sf::sleep(elapsedTime);

		//rendering of level
		//level->render(window);
	}
	EXP::log("[Info]Renderer stops running in this thread: " + utils::tostring(this));
}

void Renderer::launch()
{
	if (!running)
	{
		EXP::log("[Info]Launching Renderer in new thread: " + utils::tostring(this));
		//WORK start run in new thread
		running = true;
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
		//WORK terminate simulation thread
		running = false;
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
