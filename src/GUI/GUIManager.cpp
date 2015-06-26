#include <GUI\GUIManager.hpp>

GUIManager::GUIManager(AssetManager* _assets) : Responsive(_assets)
{
	EXP::log("[Info]Constructing GUIManager... " + utils::tostring(this));
	assets->addFont("Mono", "C:/Windows/Fonts/lucon.ttf");
	assets->getFont("Mono")->load();
	assets->addTexture("missing", "./content/stock/texture/missing.png");
	assets->getTexture("missing")->load();

	testMenu = new GUIMenu(assets);
	testLabel = new Label(assets);
	testButton = new Button(assets);
	testLabel->setX(15);
	testButton->setX(30);
	testButton->setY(100);
	testMenu->setBorderColor(sf::Color::Red);
	testMenu->addElement(testLabel);
	testMenu->addElement(testButton);
	this->addMenu(testMenu);

	EXP::log("[Info]GUIManager has been constructed: " + utils::tostring(this));
}
GUIManager::~GUIManager()
{
	EXP::log("[Info]Destructing GUIManager... " + utils::tostring(this));
	EXP::log("[Info]Forcefully removing menus: " +  utils::tostring(this));
	
	delete testMenu;
	testMenu = nullptr;
	delete testLabel;
	testLabel = nullptr;
	delete testButton;
	testButton = nullptr;

	while (menus.size() > 0)
	{
		removeMenu(0);
	}
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
void GUIManager::handleEvent(sf::RenderWindow& _target, sf::Event* _event)
{
	for (auto it : menus)
	{
		it->handleEvent(_target, _event);
	}
}
