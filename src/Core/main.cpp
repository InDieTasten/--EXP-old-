//includes
#include <Utilities/VERSION.hpp>
#include <Utilities/Logger.hpp>
#include <iostream>
#include <conio.h>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <Core\EventThread.hpp>
#include <Core\Databank.hpp>

extern void ug::log(std::string);

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}



int main(int argc, char *argv[])
{
	ug::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow App(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	App.setActive(false);

	EventThread eventThread(&App);

	Databank* databank = new Databank(&App, &eventThread);

	databank->getLevel()->addSystem(new string("test"));
	databank->getLevel()->getSystem("test")->getThreadManager()->launch();

	eventThread.run();

	ug::log("[Info]Game quit!");
	getchar();
	return EXIT_SUCCESS;
}
