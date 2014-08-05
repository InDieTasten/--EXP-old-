#include "Label.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS

void Label::Setup()
{

}
void Label::Update(DataBank* _dataLink, int _x, int _y, std::string _id)
{
    displayText.setString(DisplayText);
    displayText.setPosition((float)_x,(float)_y);
    displayText.setFont(*_dataLink->FontGet("$_menuTitle"));
    displayText.setCharacterSize(12.0);
}
void Label::Render(DataBank* _dataLink, int _x, int _y, std::string _id)
{
    _dataLink->renderWindow->draw(displayText);
}
void Label::handleEvent(DataBank* _dataLink, sf::Event* _event, int _x, int _y, std::string _id)
{

}
