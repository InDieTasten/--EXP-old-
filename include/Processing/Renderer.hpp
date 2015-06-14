#ifndef _Renderer_hpp_
#define _Renderer_hpp_

#include <Utilities\Conversion.hpp>
#include <Utilities\Logger.hpp>

class Renderer
{
private:
	bool running;

	sf::RenderWindow* window;
	System* level;

	void run(); //internal method for thread

public:
	Renderer(sf::RenderWindow* _window, System* _level);
	~Renderer();

	void launch();
	void terminate();

	void setWindow(sf::RenderWindow* _window);
	void setLevel(System* _level);
	sf::RenderWindow* getWindow();
	System* getLevel();
};

#endif // !_Renderer_hpp_
