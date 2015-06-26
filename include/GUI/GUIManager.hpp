#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <SFML\Graphics.hpp>
#include <GUI\Responsive.hpp>
#include <GUI\GUIMenu.hpp>
#include <Assets\AssetManager.hpp>
#include <GUI\Elements\InputField.hpp>
#include <GUI\Elements\Label.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class GUIManager : public sf::Drawable, public Responsive
{
private:
	std::vector<GUIMenu*> menus;

	GUIMenu* testMenu;
	Label* testLabel;

public:
	GUIManager(AssetManager* _assets);
	~GUIManager();

	int addMenu(GUIMenu*);
	GUIMenu* getMenu(int);
	void removeMenu(int);

	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
	void handleEvent(sf::RenderWindow& _target, sf::Event* _event);
};

#endif // !_GUIManager_hpp_
