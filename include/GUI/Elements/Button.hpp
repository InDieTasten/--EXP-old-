#ifndef _Button_hpp_
#define _Button_hpp_

#include <SFML\Graphics.hpp>
#include <GUI\GUIElement.hpp>
#include <SFML\Text.hpp>

#include <Utilities\UI.hpp>
#include <Utilities\Logger.hpp>
#include <Utilities\Conversion.hpp>

class Button : public GUIElement
{
private:
	int width;
	int height;
	std::string text;
	std::string font;
	sf::Color borderColor;
	sf::Color backColor;
	sf::Color textColor;
	bool enabled;

	mutable struct Components {
		sf::RectangleShape body;
		Text text;
	} components;
	struct States {
		bool clicking = false;
		bool hover = false;
	} states;
public:
	Button(AssetManager* _assets);
	~Button();

	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void handleEvent(sf::RenderWindow& target, sf::Event* _event);

	void setWidth(int);
	void setHeight(int);
	void setText(std::string);
	void setFont(std::string);
	void setBorderColor(sf::Color);
	void setBackColor(sf::Color);
	void setTextColor(sf::Color);
	void setEnabled(bool);
	int getWidth();
	int getHeight();
	std::string getText();
	std::string getFont();
	sf::Color getBorderColor();
	sf::Color getBackColor();
	sf::Color getTextColor();
	bool getEnabled();
};

#endif // !_Button_hpp_
