//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);
extern void EXP::init();

#include <list>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <string>

void listener(int x, int y)
{
	EXP::log("[DEBUG]");
	return;
}

int main(int argc, char *argv[])
{
	EXP::init();
	EXP::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow Window(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	std::list<void(*)(int, int)> listeners;

	listeners.push_back(&listener);

	for (auto it : listeners)
	{
		it(5, 6);
	}

	Window.close();
	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
