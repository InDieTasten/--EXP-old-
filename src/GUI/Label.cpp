#include <GUI\Label.hpp>

Label::Label(AssetManager* _assets) : GUIElement(_assets)
{
	type = ElementType::Label;

	text = "Default Label text";
	font = "Label";
	textColor = sf::Color::White;
	textSize = 14;

	update();

	EXP::log("[Info]Label has been constructed: " + utils::tostring(this));
}
Label::~Label()
{
	EXP::log("[Info]Destructing Label... " + utils::tostring(this));
	EXP::log("[Info]Label has been destructed: " + utils::tostring(this));
}

void Label::update()
{
	components.text.setFont(*assets->getFont(font)->get());
	components.text.setPosition(x, y);
	components.text.setCharacterSize(textSize);
	components.text.setColor(textColor);
}
void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(components.text, states);
}
void Label::handleEvent(sf::RenderWindow& target, sf::Event* _event)
{
	//WORK
}

void Label::setText(std::string _text)
{
	text = _text;
}
void Label::setFont(std::string _font)
{
	font = _font;
}
void Label::setTextColor(sf::Color _color)
{
	textColor = _color;
}
std::string Label::getText()
{
	return text;
}
std::string Label::getFont()
{
	return font;
}
sf::Color Label::getTextColor()
{
	return textColor;
}
