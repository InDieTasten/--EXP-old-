#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{
    multiline = true;
    cursor = 0;
    line = 0;
    for(std::iterator it=text.begin();;)
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

    c.setPosition((float)_x+(cursor*7),(float)_y+(line*12));
    c.setSize(sf::Vector2f(7,12));
    c.setFillColor(sf::Color(20,150,20,150));
    c.setOutlineThickness(1.0f);
    c.setOutlineColor(sf::Color(255,255,255,50));
}
void TextBox::Render(DataBank* _dataLink, int _x, int _y, std::string _id)
{
    _dataLink->renderWindow->draw(rect);
    _dataLink->renderWindow->draw(c);
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
                    cursor = 0;
                }
                else if(multiline == true)
                {
                    text+=10;
                    line++;
                    cursor = 0;
                }
            }
            else if(_event->key.code == 59)
            {
                clear = 1;
                if(cursor>=1)
                {
                    tmp = text.substr (0,(cursor-1));
                    tmp2 = text.substr (cursor,text.size());
                    cursor--;
                    text = tmp + tmp2;
                }
            }
            else if(_event->key.code == 72)
            {
                if(cursor < text.size())
                {
                    cursor++;
                }
            }
            else if(_event->key.code == 71)
            {
                if(cursor >= 1)
                {
                    cursor--;
                }
            }
            else if(_event->key.code == 73)
            {
                if(line >= 1)
                {
                    line--;
                }
            }
            else if(_event->key.code == 74)
            {
                if(line >= 1)
                {
                    line++;
                }
            }
            else if(_event->key.code == sf::Keyboard::Delete)
            {
                if(cursor < text.size())
                {
                    tmp = text.substr (0,(cursor));
                    tmp2 = text.substr (cursor+1,text.size());
                    text = tmp + tmp2;
                }
            }
            else if(_event->key.code == sf::Keyboard::End)
            {
                cursor = text.size();
            }
            else if(_event->key.code == sf::Keyboard::Home)
            {
                cursor = 0;
            }
        }
        else if(_event->type == sf::Event::TextEntered && clear == 0)
        {
            if (_event->text.unicode < 128 && _event->text.unicode > 31)
            {
                tmp = text.substr (0,(cursor));
                tmp2 = _event->text.unicode;
                tmp3 = text.substr (cursor,text.size());
                text = tmp +tmp2 + tmp3;
                cursor++;
            }
        }
        clear = 0;
    }
}
