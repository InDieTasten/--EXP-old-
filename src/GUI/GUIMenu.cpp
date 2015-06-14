#include <GUI\GUIMenu.hpp>

GUIMenu::GUIMenu()
{

	EXP::log("[Info]GUIMenu has been constructed: " + utils::tostring(this));
}
GUIMenu::~GUIMenu()
{

	EXP::log("[Info]GUIMenu has been destructed: " + utils::tostring(this));
}

int GUIMenu::addElement(GUIElement& _element)
{
	elements.push_back(_element);
	return elements.size() - 1;
}
GUIElement& GUIMenu::getElement(int _pos)
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
