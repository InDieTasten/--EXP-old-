#ifndef _Label_hpp_
#define _Label_hpp_

#include <GUI\GUIElement.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Label : GUIElement
{
private:
	std::string text;
public:
	Label();
	~Label();

	void draw(sf::RenderTarget* target, sf::RenderStates states);
	void handleEvent(sf::Event* _event);

	void setText(std::string);
	std::string getText();
};

#endif // !_Label_hpp_