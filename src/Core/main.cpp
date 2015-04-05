//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>
#include <Input\EventManager.hpp>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);
extern void EXP::init();

#include <list>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace EXP {
	EventManager* eventManager = nullptr;
}

void gameQuit(sf::Event::KeyEvent _event)
{
	if (_event.code == sf::Keyboard::Escape)
	{
		EXP::eventManager->terminate();
	}
}

int main(int argc, char *argv[])
{
	EXP::init();
	EXP::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow Window(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	EXP::eventManager = new EventManager(&Window);
	EXP::eventManager->addKeyRelease(&gameQuit);

	EXP::eventManager->listen();

	delete EXP::eventManager;
	EXP::eventManager = nullptr;
	Window.close();
	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
