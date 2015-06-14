#ifndef _Renderer_hpp_
#define _Renderer_hpp_

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <Data\System.hpp>
#include <GUI\GUIManager.hpp>

#include <Utilities\Conversion.hpp>
#include <Utilities\Logger.hpp>

class Renderer
{
private:
	sf::Thread thread;
	bool running;

	sf::RenderWindow* window;
	GUIManager* guiManager;
	System* level;

	void run(); //internal method for thread

public:
	Renderer(sf::RenderWindow* _window, GUIManager* _guiManager, System* _level);
	~Renderer();

	void launch();
	void terminate();

	void setWindow(sf::RenderWindow* _window);
	void setLevel(System* _level);
	sf::RenderWindow* getWindow();
	System* getLevel();
};

#endif // !_Renderer_hpp_
