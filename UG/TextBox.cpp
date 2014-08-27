#include "TextBox.hpp"

//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void TextBox::Setup()
{
    multiline = false;
    cursor = 0;
    line = 0;
    std::list<std::string>::iterator it=text.begin();
    text.push_back("");

}
void TextBox::Update(int _x, int _y,std::string _id)
{
    for(std::list<std::string>::iterator it = text.begin(); it != text.end(); ++it)
    {
        std::list<sf::Text>::iterator it1 = text1.begin();
        it1->setString(*it);

        it1->setPosition((float)_x, (float)_y+(12*line));
        it1->setFont(*dLink->FontGet("$_menuTitle"));
        it1->setCharacterSize(12.0);
        it1->setScale(1.0,1.0);
        ++it1;
    }

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
void TextBox::Render(int _x, int _y, std::string _id)
{
    for(std::list<sf::Text>::iterator it1 = text1.begin(); it1 != text1.end(); ++it1)
    {
        dLink->renderWindow->draw(rect);
        dLink->renderWindow->draw(c);
        dLink->renderWindow->draw(*it1);
    }
}
void TextBox::handleEvent(sf::Event* _event, int _x, int _y,std::string _id)
{
    if(isActive)
    {
        //h‰‰‰‰‰‰‰‰‰‰sslich
        a = line;
        for(std::list<std::string>::iterator it = text.begin();a >= 0; it++){a--;}

        if(_event->type == sf::Event::KeyPressed)
        {
            if(_event->key.code == 58)
            {
                clear = 1;
                if(multiline == false)
                {
                    std::list<std::string>::iterator itt =text.begin();
                    std::list<std::string> x;
                    x.push_back("textbox_submit");
                    x.push_back(_id);
                    x.push_back(*itt);
                    dLink->pushEvent(x);
                    *itt="";
                    cursor = 0;
                }
                else if(multiline == true)
                {
                    line++;
                    cursor = 0;
                }
            }
            else if(_event->key.code == 59)
            {
                clear = 1;
                if(cursor>=1)
                {
                    tmp = it->substr(0,(cursor-1));
                    tmp2 = it->substr(cursor,it->size());
                    cursor--;
                    *it = tmp + tmp2;
                }
            }
            else if(_event->key.code == 72)
            {
                if(cursor < it->size())
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
                if(cursor < it->size())
                {
                    tmp = it->substr (0,(cursor));
                    tmp2 = it->substr (cursor+1,it->size());
                    *it = tmp + tmp2;
                }
            }
            else if(_event->key.code == sf::Keyboard::End)
            {
                cursor = it->size();
            }
            else if(_event->key.code == sf::Keyboard::Home)
            {
                cursor = 0;
            }
        }
        else if(_event->type == sf::Event::TextEntered && clear == 0)
        {
            if (_event->it->unicode < 128 && _event->it->unicode > 31)
            {
                tmp = it->substr (0,(cursor));
                tmp2 = _event->it->unicode;
                tmp3 = it->substr (cursor,it->size());
                *it = tmp +tmp2 + tmp3;
                cursor++;
            }
        }
        clear = 0;
    }
}
void TextBox::handleSoftEvent(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
void TextBox::handleTask(std::list<std::string> _args, int _x, int _y, std::string _id)
{

}
