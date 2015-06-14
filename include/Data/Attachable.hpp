#ifndef _Attachable_hpp_
#define _Attachable_hpp_

#include <SFML\Graphics.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Attachable
{
private:
	sf::Vector2f position;
	float rotation;
	sf::Vector2f size;
public:
	Attachable();
	~Attachable();

	//SET
	void setPosition(sf::Vector2f);
	void setSize(sf::Vector2f);
	void setRotation(float);
	//DISPLACE
	void movePosition(sf::Vector2f);
	void moveSize(sf::Vector2f);
	void moveRotation(float);
	//GET
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	float getRotation();
};

#endif // !_Attachable_hpp_
