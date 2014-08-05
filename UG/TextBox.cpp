#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{
    multiline = false;
}
void TextBox::Update(DataBank* _dataLink, int _x, int _y,std::string _id)
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
void TextBox::Render(DataBank* _dataLink, int _x, int _y, std::string _id)
{
    _dataLink->renderWindow->draw(rect);
    _dataLink->renderWindow->draw(text1);
}
void TextBox::handleEvent(DataBank* datalink,sf::Event* _event, int _x, int _y,std::string _id)
{
    if(isActive)
    {
        if(_event->type == sf::Event::KeyPressed)
        {
            if(_event->key.code == 58)
            {
                clear = 1;
                if(multiline == false)
                {
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    x.push_back(text);
                    datalink->pushEvent(x);
                    text="";
                }
                else
                {
                    text+=10;
                }
            }
            else if(_event->key.code == 59)
            {
                clear = 1;
                if(text.size()>=1)
                {
                    text =text.substr (0,text.size()-1);
                }
            }
        }
        else if(_event->type == sf::Event::TextEntered && clear == 0)
        {
            if (_event->text.unicode < 128 && _event->text.unicode > 31)
            {
                if(!multiline)
                {
                    text += _event->text.unicode;
                }
            }
        }
        clear = 0;
    }
}
