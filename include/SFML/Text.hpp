#ifndef _Text_hpp_
#define _Text_hpp_

#include <SFML\Graphics.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Text : public sf::Drawable, public sf::Transformable
{
private:
	mutable sf::Text text;
	mutable const sf::Font* newFont;
public:
	Text();
	~Text();

	void setFont(const sf::Font& font);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setString(const sf::String& string);
	void setCharacterSize(unsigned int size);
	void setStyle(sf::Uint32 style);
	void setColor(const sf::Color& color);
	const sf::String& getString() const;
	const sf::Font* getFont() const;
	unsigned int getCharacterSize() const;
	sf::Uint32 getStyle() const;
	const sf::Color& getColor() const;
	sf::Vector2f findCharacterPos(std::size_t index) const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& position);
	void setRotation(float angle);
	void setScale(float factorX, float factorY);
	void setScale(const sf::Vector2f& factors);
	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f& origin);
	const sf::Vector2f& getPosition() const;
	float getRotation() const;
	const sf::Vector2f& getScale() const;
	const sf::Vector2f& getOrigin() const;
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f& offset);
	void rotate(float angle);
	void scale(float factorX, float factorY);
	void scale(const sf::Vector2f& factor);
	const sf::Transform& getTransform() const;
	const sf::Transform& getInverseTransform() const;
};

#endif // !_Text_hpp_
