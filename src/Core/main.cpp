//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>

#include <mutex>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <Assets\TextureManager.hpp>


int main(int argc, char *argv[])
{
	EXP::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow Window(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	sf::Thread thrd(&EXP::log, "[Test]");
	thrd.launch();

	sf::sleep(sf::seconds(1));

	Window.close();
	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
