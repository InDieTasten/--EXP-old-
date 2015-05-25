//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <SFML\Graphics.hpp>
#include <Input\EventManager.hpp>

extern sf::Mutex loggermtx;
extern void EXP::log(std::string);
extern void EXP::init();


//TESTZONE START
#include <..\EXP-ExpandedExploration\TestCode.hpp>
extern void EXP::testCode();
//TESTZONE END


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
int gameStart(int argc, char *argv[])
{
	EXP::init();
	EXP::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow Window(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
	sf::View view = Window.getDefaultView();
	view.setCenter(0.0f, 0.0f);
	Window.setView(view);

	EXP::eventManager = new EventManager(&Window);
	EXP::eventManager->addKeyRelease(&gameQuit);

	EXP::eventManager->listen();

	delete EXP::eventManager;
	EXP::eventManager = nullptr;

	Window.close();

	EXP::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
void test();
int main(int argc, char *argv[])
{
	//Running test code
	try {
		EXP::testCode();
	}
	catch (std::exception ex) {
		EXP::log("[FATAL]Test code failed: " + std::string(ex.what()));
		return EXIT_FAILURE;
	}
	//Running game code
	gameStart(argc, argv);
	return EXIT_SUCCESS;
}

void test()
{
	//
}