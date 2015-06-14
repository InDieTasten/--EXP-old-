#ifndef _GraphicalInfo_hpp_
#define _GraphicalInfo_hpp_

#include <SFML\Graphics.hpp>
#include <Assets\Texture.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class GraphicalInfo : private sf::Drawable
{
protected:
	sf::Texture* texture;
public:
	GraphicalInfo();
	~GraphicalInfo();

	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states);

	//SET
	void setTexture(sf::Texture* _texture);
	//GET
	sf::Texture* getTexture();
};

#endif // !_GraphicalInfo_hpp_
