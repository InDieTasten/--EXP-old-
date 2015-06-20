#ifndef _GUIElement_hpp_
#define _GUIElement_hpp_

#include <SFML\Graphics.hpp>
#include <GUI\Responsive.hpp>
#include <Data\Taggable.hpp>

class GUIElement : sf::Drawable, Responsive, Taggable
{
public:
	enum ElementType{
		Label,
		Button,
		InputField,
	};
protected:
	ElementType type;
	int x;
	int y;
public:
	GUIElement(AssetManager* _assets);
	~GUIElement();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void handleEvent(sf::RenderTarget& target, sf::Event* _event) = 0;

	void setX(int);
	void setY(int);
	int getX();
	int getY();
};

#endif
