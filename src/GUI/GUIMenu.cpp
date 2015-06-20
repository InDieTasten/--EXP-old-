#include <GUI\GUIMenu.hpp>

GUIMenu::GUIMenu(AssetManager* _assets) : Responsive(_assets)
{
	height = 200;
	width = 200;
	x = 1;
	y = 1;

	title = "Undefined MenuTitle";

	update();
	EXP::log("[Info]GUIMenu has been constructed: " + utils::tostring(this));
}
GUIMenu::~GUIMenu()
{

	EXP::log("[Info]GUIMenu has been destructed: " + utils::tostring(this));
}

void GUIMenu::update()
{
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

	components.closeButtonRect.setSize(sf::Vector2f(14, 14));
	components.closeButtonRect.setPosition(x + width - 15, y + 1);
	components.closeButtonRect.setFillColor(sf::Color(255, !state.quitting * 255, !state.quitting * 255, state.closeButtonHover * 255));
	components.closeButtonRect.setOutlineColor(sf::Color(state.closeButtonHover * 255, !state.quitting * 255, !state.quitting * state.closeButtonHover * 255, 255));
	components.closeButtonRect.setOutlineThickness(-1.0f);

	components.closeButtonCross.setPrimitiveType(sf::PrimitiveType::Lines);
	components.closeButtonCross.clear();
	components.closeButtonCross.append(sf::Vertex(sf::Vector2f(x + width - 13, y + 3),  sf::Color(!state.closeButtonHover * 255, !state.closeButtonHover * 255, !state.closeButtonHover * 255))); //upper left
	components.closeButtonCross.append(sf::Vertex(sf::Vector2f(x + width - 3, y + 13),  sf::Color(!state.closeButtonHover * 255, !state.closeButtonHover * 255, !state.closeButtonHover * 255))); //lower right
	components.closeButtonCross.append(sf::Vertex(sf::Vector2f(x + width - 13, y + 13), sf::Color(!state.closeButtonHover * 255, !state.closeButtonHover * 255, !state.closeButtonHover * 255))); //lower left
	components.closeButtonCross.append(sf::Vertex(sf::Vector2f(x + width - 3, y + 3),   sf::Color(!state.closeButtonHover * 255, !state.closeButtonHover * 255, !state.closeButtonHover * 255))); //upper right


	components.titleText.setPosition(x + 3, y - 1);
	components.titleText.setString(title);
	components.titleText.setCharacterSize(14);
	components.titleText.setFont(*assets->getFont("MenuTitle")->get());
}
void GUIMenu::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	if (!state.open)
		return;
	_target.draw(components.titleRect, _states);
	_target.draw(components.bodyRect, _states);
	_target.draw(components.closeButtonRect, _states);
	_target.draw(components.closeButtonCross, _states);
	_target.draw(components.titleText, _states);


	_states.transform.translate(sf::Vector2f((float)x, (float)y+16));
	for (auto it : elements)
	{
		it->draw(_target, _states);
	}
}
void GUIMenu::handleEvent(sf::RenderWindow& target, sf::Event* _event)
{
	if (!state.open)
		return;
	sf::Vector2i mouseNow;

	switch (_event->type)
	{
	case sf::Event::MouseButtonPressed:
		state.moving = state.titleHover && !state.closeButtonHover;
		state.quitting = state.closeButtonHover;
		update();
		break;
	case sf::Event::MouseButtonReleased:
		state.moving = false;
		if (state.quitting)
		{
			close();
		}
		break;
	case sf::Event::MouseMoved:
		mouseNow  = (sf::Vector2i)target.mapPixelToCoords(sf::Vector2i(_event->mouseMove.x, _event->mouseMove.y));

		EXP::log("[DEBUG] Diff: " + utils::tostring(mouseNow.x) + " : " + utils::tostring(mouseNow.y));

		if (state.moving)
		{
			x += mouseNow.x - state.lastPosition.x;
			y += mouseNow.y - state.lastPosition.y;
			update();
		}

		if (state.quitting)
		{
			state.quitting = false;
			update();
		}
		
		state.lastPosition = mouseNow;

		state.titleHover = utils::hovering(components.titleRect.getGlobalBounds(), state.lastPosition);
		
		bool old = state.closeButtonHover;
		if (old != (state.closeButtonHover = utils::hovering(components.closeButtonRect.getGlobalBounds(), state.lastPosition)))
		{
			update();
		}

		break;
	}
	for (auto it : elements)
	{
		it->handleEvent(target, _event);
	}
}

void GUIMenu::show()
{
	state.open = true;
}
void GUIMenu::close()
{
	state.open = false;
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
