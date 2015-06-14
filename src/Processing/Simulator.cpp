#include <Processing\Simulator.hpp>

Simulator::Simulator(sf::RenderWindow* _window, System* _level) : running(false)
{
	window = _window;
	level = _level;
	EXP::log("[Info]Simulator has been  constructed: " + utils::tostring(this));
}
Simulator::~Simulator()
{

	EXP::log("[Info]Simulator has been  destructed: " + utils::tostring(this));
}

void Simulator::run()
{
	while (running)
	{
		//limiter
		//sf::sleep(elapsedTime);

		//simulation of level
		//level->simulate(frametime);
	}
}

void Simulator::launch()
{
	if (!running)
	{
		EXP::log("[Info]Launching Simulator in new thread: " + utils::tostring(this));
		//WORK start run in new thread
		running = true;
	}
	else {
		EXP::log("[Warning]Tried launching already running Simulator: " + utils::tostring(this));
	}
}
void Simulator::terminate()
{
	if (running)
	{
		EXP::log("[Info]Terminating Simulator: " + utils::tostring(this));
		//WORK terminate simulation thread
		running = false;
	}
	else {
		EXP::log("[Warning]Tried terminating already terminated Simulator: " + utils::tostring(this));
	}
}
void Simulator::setWindow(sf::RenderWindow* _window)
{
	bool tmp = running;
	if (running)
	{
		EXP::log("[Info]Terminating simulation to change target window: " + utils::tostring(this));
		terminate();
	}
		
	window = _window;

	if (tmp){
		EXP::log("[Info]Re-launching simulator after changing target window: " + utils::tostring(this));
		launch();
	}
}
void Simulator::setLevel(System* _level)
{
	bool tmp = running;
	if (running)
	{
		EXP::log("[Info]Terminating simulation to change target level: " + utils::tostring(this));
		terminate();
	}

	level = _level;

	if (tmp){
		EXP::log("[Info]Re-launching simulator after changing target level: " + utils::tostring(this));
		launch();
	}
}
sf::RenderWindow* Simulator::getWindow()
{
	return window;
}
System* Simulator::getLevel()
{
	return level;
}
