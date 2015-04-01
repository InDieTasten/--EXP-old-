//includes
#include <Utilities\VERSION.hpp>
#include <Utilities\Logger.hpp>
#include <iostream>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <Core\EventThread.hpp>
#include <Core\Databank.hpp>

#include <mutex>
#include <thread>

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



void infinite()
{
	ug::log("running");
	ug::log("stopped");
}

int main(int argc, char *argv[])
{
	ug::log("[Info]Game is launching in version: " + VERSION::version);
	sf::RenderWindow App(sf::VideoMode(1280, 720, 32), VERSION::name + " " + VERSION::version, sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

	ug::log("[THREAD] 1");
	thread x(infinite);
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 2");
	ug::log("[THREAD] 3");
	ug::log("[THREAD] 3.5");
	ug::log("[THREAD] 4");



	EventThread* eThread = new EventThread(&App);

	eThread->run();

	delete eThread;
	eThread = nullptr;

	App.close();
	ug::log("[Info]Game quit!");
	return EXIT_SUCCESS;
}
