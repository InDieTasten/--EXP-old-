#ifndef _GUIManager_hpp_
#define _GUIManager_hpp_

#include <SFML\Graphics.hpp>
#include <GUI\Responsive.hpp>
#include <GUI\GUIMenu.hpp>
#include <Assets\AssetManager.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class GUIManager : public sf::Drawable, public Responsive
{
private:
	std::vector<GUIMenu*> menus;
public:
	GUIManager(AssetManager* _assets);
	~GUIManager();

	int addMenu(GUIMenu*);
	GUIMenu* getMenu(int);
	void removeMenu(int);

	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
	void handleEvent(sf::RenderTarget& _target, sf::Event* _event);
};

#endif // !_GUIManager_hpp_
