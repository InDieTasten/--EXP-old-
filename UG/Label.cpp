#include "Label.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS

void Label::Setup()
{

}
void Label::Update(DataBank* _dataLink, int _x, int _y)
{
    displayText.SetText(DisplayText);
    displayText.SetPosition((float)_x,(float)_y);
    displayText.SetFont(*_dataLink->FontGet("$_menuTitle"));
    displayText.SetSize(12.0);
}
void Label::Render(DataBank* _dataLink)
{
    _dataLink->renderWindow->Draw(displayText);
}
void Label::handleEvent(sf::Event* _event, const sf::Input* _input)
{

}
