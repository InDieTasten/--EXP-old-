#ifndef _Simulator_hpp_
#define _Simulator_hpp_

#include <SFML\Graphics.hpp>
#include <Data\System.hpp>

#include <Utilities\Conversion.hpp>
#include <Utilities\Logger.hpp>

class Simulator
{
private:
	bool running;

	sf::RenderWindow* window;
	System* level;

	void run(); //internal method for thread

public:
	Simulator(sf::RenderWindow* _window, System* _level);
	~Simulator();

	void launch();
	void terminate();

	void setWindow(sf::RenderWindow* _window);
	void setLevel(System* _level);
	sf::RenderWindow* getWindow();
	System* getLevel();
};

#endif // !_Simulator_hpp_
