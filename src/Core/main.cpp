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



#include <Input\EventManager.hpp>
namespace EXP {
	EventManager* eventManager;
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

	EventManager man(&Window);
	EXP::eventManager = &man;

	man.addKeyPress(&gameQuit);

	man.listen();

	Window.close();
	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
