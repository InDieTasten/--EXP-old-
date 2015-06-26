#include <GUI\Elements\Button.hpp>

Button::Button(AssetManager* _assets) : GUIElement(_assets)
{
	type = ElementType::Button;

	width = 120;
	height = 20;
	text = "Undefined";
	font = "Mono";
	borderColor = sf::Color(0, 255, 0, 255);
	backColor = sf::Color(80, 80, 80, 64);
	textColor = sf::Color::White;
	enabled = true;

	EXP::log("[Info]Button has been constructed: " + utils::tostring(this));
}
Button::~Button()
{
	EXP::log("[Info]Button has been destructed: " + utils::tostring(this));
}

void Button::update()
{
	components.body.setPosition(x, y);
	components.body.setSize(sf::Vector2f(width, height));
	components.body.setFillColor(backColor);
	components.body.setOutlineColor(borderColor * sf::Color(255, 255, 255, 64 + enabled * (127+64)));
	components.body.setOutlineThickness(1.0f);

	components.text.setString(text);
	components.text.setColor(textColor);
	components.text.setFont(*assets->getFont(font)->get());
	components.text.setCharacterSize(14);
	components.text.findCharacterPos(1024);

}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect bounds = components.text.getGlobalBounds();
	components.text.setPosition(sf::Vector2f((int)(x + width / 2 - bounds.width / 2), (int)(y-2 + height / 2 - bounds.height / 2)));
	target.draw(components.body, states);
	target.draw(components.text, states);
}
void Button::handleEvent(sf::RenderWindow& target, sf::Event* _event)
{
	//Button handling routine (WORK)
}

void Button::setWidth(int _width)
{
	width = _width;
	update();
}
void Button::setHeight(int _height)
{
	height = _height;
	update();
}
void Button::setText(std::string _text)
{
	text = _text;
	update();
}
void Button::setFont(std::string _font)
{
	font = _font;
	update();
}
void Button::setBorderColor(sf::Color _color)
{
	borderColor = _color;
	update();
}
void Button::setBackColor(sf::Color _color)
{
	backColor = _color;
	update();
}
void Button::setTextColor(sf::Color _color)
{
	textColor = _color;
	update();
}
void Button::setEnabled(bool _enabled)
{
	enabled = _enabled;
	update();
}
int Button::getWidth()
{
	return width;
}
int Button::getHeight()
{
	return height;
}
std::string Button::getText()
{
	return text;
}
std::string Button::getFont()
{
	return font;
}
sf::Color Button::getBorderColor()
{
	return borderColor;
}
sf::Color Button::getBackColor()
{
	return backColor;
}
sf::Color Button::getTextColor()
{
	return textColor;
}
bool Button::getEnabled()
{
	return enabled;
}
