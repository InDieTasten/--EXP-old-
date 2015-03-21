//includes
#include <Utilities/VERSION.hpp>
#include <Utilities/Logger.hpp>
#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <Core\EventThread.hpp>
#include <Core\Databank.hpp>

extern std::mutex loggermtx;
extern void ug::log(std::string);

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace ug{
	void terminate();
	EventThread* eventthread;
	GraphicsThread* graphicsthread;
	Databank* databank;
	sf::RenderWindow* renderwindow;
}

class test
{
public:
	thread x;
	bool running;
	void func() { running = true; while (running){} }
	void launch() { x = thread(&func, this); }
	void terminate() { if (x.joinable()){ running = false; x.join(); } }
};

int main(int argc, char *argv[])
{
	ug::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow App(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);


	ug::log("[THREAD] 1");
	test* a = new test();
	ug::log("[THREAD] 2");
	a->launch();
	ug::log("[THREAD] 3");
	a->terminate();
	ug::log("[THREAD] 4");
	delete a;
	a = nullptr;



	EventThread* eThread = new EventThread(&App);

	eThread->run();

	delete eThread;
	eThread = nullptr;

	App.close();
	ug::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
