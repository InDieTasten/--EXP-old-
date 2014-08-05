#include "Label.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS

void Label::Setup()
{

}
void Label::Update(DataBank* _dataLink, int _x, int _y)
{
    displayText.setString(DisplayText);
    displayText.setPosition((float)_x,(float)_y);
    displayText.setFont(*_dataLink->FontGet("$_menuTitle"));
    displayText.setCharacterSize(12.0);
}
void Label::Render(DataBank* _dataLink)
{
    _dataLink->renderWindow->draw(displayText);
}
void Label::handleEvent(sf::Event* _event)
{

}
