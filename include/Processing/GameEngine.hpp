#ifndef _GameEngine_hpp_
#define _GameEngine_hpp_

#include <SFML\Graphics.hpp>
#include <Data\System.hpp>
#include <Input\EventManager.hpp>
#include <Processing\Renderer.hpp>
#include <Processing\Simulator.hpp>
#include <GUI\InputField.hpp>
#include <Assets\TextureManager.hpp>
#include <Assets\FontManager.hpp>

#include <Utilities\Conversion.hpp>
#include <Utilities\Logger.hpp>

class GameEngine
{
private:
	sf::RenderWindow* gameWindow;
	GUIManager* guiManager;
	EventManager* eventManager;
	Renderer* renderer;
	Simulator* simulator;

	TextureManager textureManager;
	FontManager fontManager;

	System* level;
	sf::View defaultView;

public:


	GameEngine();
	~GameEngine();

	void launch();
};

#endif // !_GameEngine_hpp_
