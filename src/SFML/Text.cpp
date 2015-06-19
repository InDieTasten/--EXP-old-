#include <SFML\Text.hpp>

Text::Text()
{
	newFont = nullptr;
	EXP::log("[Info]Text has been constructed: " + utils::tostring(this));
}
Text::~Text()
{
	EXP::log("[Info]Text has been destructed: " + utils::tostring(this));
}

void Text::setFont(const sf::Font& font)
{
	newFont = &font;
}
void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (newFont)
	{
		text.setFont(*newFont);
		newFont = nullptr;
	}
	target.draw(text, states);
}
void Text::setString(const sf::String& string)
{
	text.setString(string);
}
void Text::setCharacterSize(unsigned int size)
{
	text.setCharacterSize(size);
}
void Text::setStyle(sf::Uint32 style)
{
	text.setStyle(style);
}
void Text::setColor(const sf::Color& color)
{
	text.setColor(color);
}
const sf::String& Text::getString() const
{
	return text.getString();
}
const sf::Font* Text::getFont() const
{
	return text.getFont();
}
unsigned int Text::getCharacterSize() const
{
	return text.getCharacterSize();
}
sf::Uint32 Text::getStyle() const
{
	return text.getStyle();
}
const sf::Color& Text::getColor() const
{
	return text.getColor();
}
sf::Vector2f Text::findCharacterPos(std::size_t index) const
{
	return text.findCharacterPos(index);
}
sf::FloatRect Text::getLocalBounds() const
{
	return text.getLocalBounds();
}
sf::FloatRect Text::getGlobalBounds() const
{
	return text.getGlobalBounds();
}
void Text::setPosition(float x, float y)
{
	text.setPosition(x, y);
}
void Text::setPosition(const sf::Vector2f& position)
{
	text.setPosition(position);
}
void Text::setRotation(float angle)
{
	text.setRotation(angle);
}
void Text::setScale(float factorX, float factorY)
{
	text.setScale(factorX, factorY);
}
void Text::setScale(const sf::Vector2f& factors)
{
	text.setScale(factors);
}
void Text::setOrigin(float x, float y)
{
	text.setOrigin(x, y);
}
void Text::setOrigin(const sf::Vector2f& origin)
{
	text.setOrigin(origin);
}
const sf::Vector2f& Text::getPosition() const
{
	return text.getPosition();
}
float Text::getRotation() const
{
	return text.getRotation();
}
const sf::Vector2f& Text::getScale() const
{
	return text.getScale();
}
const sf::Vector2f& Text::getOrigin() const
{
	return text.getOrigin();
}
void Text::move(float offsetX, float offsetY)
{
	text.move(offsetX, offsetY);
}
void Text::move(const sf::Vector2f& offset)
{
	text.move(offset);
}
void Text::rotate(float angle)
{
	text.rotate(angle);
}
void Text::scale(float factorX, float factorY)
{
	text.scale(factorX, factorY);
}
void Text::scale(const sf::Vector2f& factor)
{
	text.scale(factor);
}
const sf::Transform& Text::getTransform() const
{
	return text.getTransform();
}
const sf::Transform& Text::getInverseTransform() const
{
	return text.getInverseTransform();
}
