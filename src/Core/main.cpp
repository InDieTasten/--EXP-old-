//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>

#include <mutex>

extern std::mutex loggermtx;
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

	

	App.close();
	ug::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
