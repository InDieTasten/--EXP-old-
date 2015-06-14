#include <Processing\Simulator.hpp>

Simulator::Simulator(sf::RenderWindow* _window, System* _level) :
	running(false),
	thread(&Simulator::run, this)
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
	EXP::log("[Info]Simulator running in this thread: " + utils::tostring(this));

	sf::Clock limiter;
	limiter.restart();

	while (running)
	{
		//limiter
		sf::sleep(sf::Time(sf::milliseconds(1000.0f / 60.0f) - limiter.restart()));

		//simulation of level
		//level->simulate(frametime);
	}
	EXP::log("[Info]Simulator stops running in this thread: " + utils::tostring(this));
}

void Simulator::launch()
{
	if (!running)
	{
		EXP::log("[Info]Launching Simulator in new thread: " + utils::tostring(this));
		running = true;
		thread.launch();
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
		running = false;
		thread.wait();
		sf::sleep(sf::seconds(1));
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
