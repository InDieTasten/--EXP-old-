#include <GUI\GUIMenu.hpp>

GUIMenu::GUIMenu()
{
	x = 15;
	y = 15;
	height = 200;
	width = 200;
	EXP::log("[Info]GUIMenu has been constructed: " + utils::tostring(this));
}
GUIMenu::~GUIMenu()
{

	EXP::log("[Info]GUIMenu has been destructed: " + utils::tostring(this));
}

void GUIMenu::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	EXP::log("DEBUG1");
	_states.transform.translate(sf::Vector2f((float)x, (float)y));
	EXP::log("DEBUG2");
	for (auto it : elements)
	{
		it->draw(_target, _states);
	}
	EXP::log("DEBUG3");
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
}
void GUIMenu::setY(int _y)
{
	y = _y;
}
void GUIMenu::setWidth(int _width)
{
	width = _width;
}
void GUIMenu::setHeight(int _height)
{
	height = _height;
}
void GUIMenu::setTitle(std::string _title)
{
	title = _title;
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
