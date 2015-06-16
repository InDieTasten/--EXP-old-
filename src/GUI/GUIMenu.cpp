#include <GUI\GUIMenu.hpp>

GUIMenu::GUIMenu(AssetManager* _assets)
{
	x = 0;
	y = 0;
	height = 200;
	width = 200;

	assets = _assets;

	update();
	EXP::log("[Info]GUIMenu has been constructed: " + utils::tostring(this));
}
GUIMenu::~GUIMenu()
{

	EXP::log("[Info]GUIMenu has been destructed: " + utils::tostring(this));
}

void GUIMenu::update()
{
	//grab assets
	asset.title = assets->getFont("identifier of font")->get();

	//update components
	components.titleRect.setSize(sf::Vector2f(width, 16));
	components.titleRect.setPosition(x, y);
	components.titleRect.setFillColor(sf::Color(80, 80, 80, 128));
	components.titleRect.setOutlineColor(sf::Color(0, 255, 0, 255));
	components.titleRect.setOutlineThickness(1.0f);

	components.bodyRect.setSize(sf::Vector2f(width, height));
	components.bodyRect.setPosition(x, y + 17); //17 because outline overlaps
	components.bodyRect.setFillColor(sf::Color(80, 80, 80, 64));
	components.bodyRect.setOutlineColor(sf::Color(0, 255, 0, 255));
	components.bodyRect.setOutlineThickness(1.0f);

	components.titleText.setCharacterSize(14);
	components.titleText.setPosition(x + 1, y + 1);
	components.titleText.setString("--My test menu--");
	components.titleText.setColor(sf::Color::White);
	components.titleText.setFont(*asset.title);

	//WORK closeButtonRect;
	//WORK closeButtonCross;
}
void GUIMenu::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(components.titleRect, _states);
	_target.draw(components.bodyRect, _states);
	_target.draw(components.titleText, _states);
	_target.draw(components.closeButtonRect, _states);
	_target.draw(components.closeButtonCross, _states);

	_states.transform.translate(sf::Vector2f((float)x, (float)y+16));
	for (auto it : elements)
	{
		it->draw(_target, _states);
	}
}
void GUIMenu::handleEvent(sf::Event* _event)
{
	for (auto it : elements)
	{
		it->handleEvent(_event);
	}
}

int GUIMenu::addElement(GUIElement* _element)
{
	elements.push_back(_element);
	return elements.size() - 1;
}
GUIElement* GUIMenu::getElement(int _pos)
{
	return elements[_pos];
}
void GUIMenu::removeElement(int _pos)
{
	elements.erase(elements.begin() + _pos);
}

void GUIMenu::setX(int _x)
{
	x = _x;
	update();
}
void GUIMenu::setY(int _y)
{
	y = _y;
	update();
}
void GUIMenu::setWidth(int _width)
{
	width = _width;
	update();
}
void GUIMenu::setHeight(int _height)
{
	height = _height;
	update();
}
void GUIMenu::setTitle(std::string _title)
{
	title = _title;
	update();
}
int GUIMenu::getX()
{
	return x;
}
int GUIMenu::getY()
{
	return y;
}
int GUIMenu::getWidth()
{
	return width;
}
int GUIMenu::getHeight()
{
	return height;
}
std::string GUIMenu::getTitle()
{
	return title;
}
