#ifndef _InputField_hpp_
#define _InputField_hpp_

#include <GUI\GUIElement.hpp>

#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class InputField : public GUIElement
{
private:
	int width;
	int height;

	std::string content;
public:
	InputField();
	~InputField();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvent(sf::Event* _event);

	void setWidth(int);
	void setHeight(int);
	void setContent(std::string);
	int getWidth();
	int getHeight();
	std::string getContent();
	
};

#endif // !_InputField_hpp_