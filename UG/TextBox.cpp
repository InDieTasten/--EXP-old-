#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{


}
void TextBox::Update(DataBank* _dataLink, int _x, int _y)
{
    text1.setString(text);
    text1.setPosition((float)_x, (float)_y);
    text1.setFont(*_dataLink->FontGet("$_menuTitle"));
    text1.setCharacterSize(12.0);
    text1.setScale(1.0,1.0);

    rect.setPosition((float)_x,(float)_y);
    rect.setSize(sf::Vector2f((float)Width,(float)Height));
    rect.setFillColor(sf::Color(20,20,20,150));
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color(255,255,255,50));
}
void TextBox::Render(DataBank* _dataLink)
{
    _dataLink->renderWindow->draw(rect);
    _dataLink->renderWindow->draw(text1);
}
void TextBox::handleEvent(sf::Event* _event, int _x, int _y)
{
    if(isActive)
    {

    }
}
