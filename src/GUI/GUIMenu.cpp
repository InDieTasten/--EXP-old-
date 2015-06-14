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
	sf::RectangleShape titleRect(sf::Vector2f(width, 16));
	titleRect.setPosition(x, y);
	titleRect.setFillColor(sf::Color(80, 80, 80, 128));
	titleRect.setOutlineColor(sf::Color(0, 255, 0, 255));
	titleRect.setOutlineThickness(1.0f);
	_target.draw(titleRect, _states);

	sf::RectangleShape bodyRect(sf::Vector2f(width, height));
	bodyRect.setPosition(x, y + 17); //17 because outline overlaps
	bodyRect.setFillColor(sf::Color(80, 80, 80, 64));
	bodyRect.setOutlineColor(sf::Color(0, 255, 0, 255));
	bodyRect.setOutlineThickness(1.0f);
	_target.draw(bodyRect, _states);

	sf::Text titleText;
	titleText.setCharacterSize(14);
	titleText.setPosition(x+1, y+1);
	titleText.setString("--My test menu--");
	titleText.setColor(sf::Color::White);
	_target.draw(titleText, _states);

	_states.transform.translate(sf::Vector2f((float)x, (float)y+14));
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
