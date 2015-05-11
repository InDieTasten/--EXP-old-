#ifndef _Attachable_hpp_
#define _Attachable_hpp_

#include <SFML\Graphics.hpp>

class Attachable
{
private:
	sf::Vector2f position;
	float rotation;
	sf::Vector2f size;
public:
	Attachable();
	~Attachable();

	void setPosition(sf::Vector2f);
	void setSize(sf::Vector2f);
	void setRotation(float);

	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	float getRotation();
};

#endif // !_Attachable_hpp_