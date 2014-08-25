#include "Label.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS

void Label::Setup()
{

}
void Label::Update(int _x, int _y, std::string _id)
{
    displayText.setString(DisplayText);
    displayText.setPosition((float)_x,(float)_y);
    displayText.setFont(*dLink->FontGet("$_menuTitle"));
    displayText.setCharacterSize(12.0);
}
void Label::Render(int _x, int _y, std::string _id)
{
    dLink->renderWindow->draw(displayText);
}
void Label::handleEvent(sf::Event* _event, int _x, int _y, std::string _id)
{

}
