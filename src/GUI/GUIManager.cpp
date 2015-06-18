#include <GUI\GUIManager.hpp>

GUIManager::GUIManager(AssetManager* _assets) : Responsive(_assets)
{
	assets->addFont("MenuTitle", "C:/Windows/Fonts/lucon.ttf");
	assets->addTexture("missing", "./content/stock/texture/missing.png");
	EXP::log("[Info]GUIManager has been constructed: " + utils::tostring(this));
}
GUIManager::~GUIManager()
{
	EXP::log("[Info]GUIManager has been destructed: " + utils::tostring(this));
}

int GUIManager::addMenu(GUIMenu* _menu)
{
	menus.push_back(_menu);
	return menus.size() - 1;
}
GUIMenu* GUIManager::getMenu(int _pos)
{
	return menus[_pos];
}
void GUIManager::removeMenu(int _pos)
{
	menus.erase(menus.begin() + _pos);
}

void GUIManager::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto it : menus)
	{
		it->draw(_target, _states);
	}
}
void GUIManager::handleEvent(sf::Event* _event)
{
	for (auto it : menus)
	{
		it->handleEvent(_event);
	}
}
